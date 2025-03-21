/*
 * This file is part of the Simutrans project under the Artistic License.
 * (see LICENSE.txt)
 */

#include <string>
#include "../../dataobj/tabfile.h"
#include "obj_node.h"
#include "text_writer.h"
#include "imagelist_writer.h"
#include "citycar_writer.h"


void citycar_writer_t::write_obj(FILE* fp, obj_node_t& parent, tabfileobj_t& obj)
{
	int i;


	uint16 const dist_weight = obj.get_int("distributionweight", 1);

	uint16 const intro_date =
		obj.get_int("intro_year", DEFAULT_INTRO_YEAR) * 12 +
		obj.get_int("intro_month", 1) - 1;

	uint16 const retire_date =
		obj.get_int("retire_year", DEFAULT_RETIRE_YEAR) * 12 +
		obj.get_int("retire_month", 1) - 1;

	uint16 const topspeed = obj.get_int("speed", 80) * 16;

	obj_node_t node(this, 10, &parent);

	// new version with intro and obsolete dates
	node.write_version(fp, 2); // version information
	node.write_uint16(fp, dist_weight);
	node.write_uint16(fp, topspeed);
	node.write_uint16(fp, intro_date);
	node.write_uint16(fp, retire_date);

	write_name_and_copyright(fp, node, obj);

	static const char* const dir_codes[] = {
		"s", "w", "sw", "se", "n", "e", "ne", "nw"
	};
	slist_tpl<std::string> keys;
	std::string str;

	for (i = 0; i < 8; i++) {
		char buf[40];

		sprintf(buf, "image[%s]", dir_codes[i]);
		str = obj.get(buf);
		keys.append(str);
	}
	imagelist_writer_t::instance()->write_obj(fp, node, keys);

	node.check_and_write_header(fp);
}
