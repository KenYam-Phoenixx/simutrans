/*
 * This file is part of the Simutrans project under the Artistic License.
 * (see LICENSE.txt)
 */

#include <locale.h>
#include <string>
#include "../../utils/simstring.h"
#include "../../dataobj/tabfile.h"
#include "../../tpl/stringhashtable_tpl.h"
#include "../../tpl/inthashtable_tpl.h"
#include "obj_node.h"
#include "obj_writer.h"
#include "image_writer.h"
#include "text_writer.h"
#include "xref_writer.h"


const char *obj_writer_t::last_name = "";

int obj_writer_t::default_image_size = 64;


void obj_writer_t::register_writer(bool main_obj)
{
	if (!writer_by_name) {
		writer_by_name = new stringhashtable_tpl<obj_writer_t*>;
		writer_by_type = new inthashtable_tpl<uint32, obj_writer_t*>;
	}
	if (main_obj) {
		writer_by_name->put(get_type_name(), this);
	}
	writer_by_type->put(get_type(), this);

	///    printf("This program can compile %s objects\n", get_type_name());
}


void obj_writer_t::write(FILE* fp, obj_node_t& parent, tabfileobj_t& obj)
{
	const char *type = obj.get("obj");
	const char *name = obj.get("name");

	obj_writer_t *writer = writer_by_name->get(type);
	if (!writer) {
		printf("Skipping unknown %s object %s\n", type, name);
		return;
	}
	// now get the image size
	image_writer_t::set_img_size(obj.get_int("cell_size",default_image_size));

	last_name = name;

	if (debuglevel >= log_t::LEVEL_WARN) {
		printf("      packing %s.%s\n", type, name);
	}

	writer->write_obj(fp, parent, obj);
}


void obj_writer_t::write_name_and_copyright(FILE* fp, obj_node_t& node, tabfileobj_t& obj)
{
	const char* name = obj.get("name");
	const char* msg = obj.get("copyright");

	last_name = name;
	text_writer_t::instance()->write_obj(fp, node, name);
	text_writer_t::instance()->write_obj(fp, node, msg);
}


bool obj_writer_t::dump_nodes(FILE* infp, int level, uint16 index)
{
	obj_node_info_t node;

	if (!obj_node_t::read_node(infp, node)  ) {
		return false;
	}

	const long next_pos = ftell(infp) + node.size;

	obj_writer_t* writer = writer_by_type->get(node.type);
	if (writer) {
		printf("%*s%03u %4.4s-node (%s)", 3 * level, " ", index, (const char*)&node.type, writer->get_type_name());
		bool ok = writer->dump_node(infp, node);
		printf("\n");
		if (!ok) {
			return false;
		}
	}

	if (fseek(infp, next_pos, SEEK_SET) != 0) {
		return false;
	}

	for (int child_idx = 0; child_idx < node.nchildren; child_idx++) {
		if (!dump_nodes(infp, level + 1, child_idx)) {
			return false;
		}
	}

	return true;
}


bool obj_writer_t::list_nodes(FILE *infp)
{
	obj_node_info_t node;

	if (!obj_node_t::read_node( infp, node ) || node.size == 0) {
		return false;
	}

	const long next_pos = ftell(infp) + node.size;

	obj_writer_t *writer = writer_by_type->get((obj_type)node.type);
	if (writer) {
		if (fseek(infp, node.size, SEEK_CUR) != 0) {
			return false;
		}

		const std::string node_name = writer->get_node_name(infp);
		printf("%-16s  %-30s  %5u  ", writer->get_type_name(), node_name.c_str(), node.nchildren);
	}
	else {
		printf("(unknown %4.4s)    %30.30s  %5.5s  ", (const char *)&node.type, " ", " ");
	}

	if (fseek(infp, next_pos, SEEK_SET) != 0) {
		return false;
	}

	size_t offset = 0;
	for (int i = 0; i < node.nchildren; i++) {
		if (!skip_nodes(infp, offset)) {
			return false;
		}
	}

	printf("%10lu\n", offset);
	return true;
}


void obj_writer_t::show_capabilites()
{
	slist_tpl<obj_writer_t*> list;
	const char *min_s="A";

	while (true) {
		const char *max_s = "zzz";
		for(auto const& i : *writer_by_name) {
			if(  STRICMP(i.key, min_s) > 0  &&  STRICMP(i.key, max_s) < 0   ) {
				max_s = i.key;
			}
		}
		if(  strcmp(max_s,"zzz")==0  ) {
			break;
		}
		printf("   %s\n", max_s);
		min_s = max_s;
	}
}


std::string obj_writer_t::name_from_next_node(FILE *fp) const
{
	std::string ret;
	obj_node_info_t node;

	if (!obj_node_t::read_node( fp, node ) || node.type!=obj_text || node.size == 0xFFFFFFFFu) {
		return "";
	}

	char *buf = new char[node.size+1];
	if (!buf) {
		return "";
	}

	if (fread(buf, node.size, 1, fp) != 1) {
		delete[] buf;
		return "";
	}

	buf[node.size] = 0;
	ret = buf;
	delete[] buf;
	return ret;
}


bool obj_writer_t::skip_nodes(FILE *fp, size_t &offset)
{
	obj_node_info_t node;

	if (!obj_node_t::read_node( fp, node ) || fseek(fp, node.size, SEEK_CUR) != 0) {
		return false;
	}

	offset += node.size;

	for (int i = 0; i < node.nchildren; i++) {
		if (!skip_nodes(fp, offset)) {
			return false;
		}
	}

	return true;
}


bool obj_writer_t::dump_node(FILE */*infp*/, const obj_node_info_t& node)
{
	printf(" %5u bytes", node.size);
	return true;
}


const char* obj_writer_t::node_writer_name(FILE* infp) const
{
	obj_node_info_t node;
	obj_node_t::read_node( infp, node );
	fseek(infp, node.size, SEEK_CUR);
	obj_writer_t* writer = writer_by_type->get(node.type);
	if (writer) {
		return writer->get_type_name();
	}
	return "unknown";
}
