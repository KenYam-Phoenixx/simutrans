#include <stdio.h>
#include <string.h>
#include "../../bauer/hausbauer.h"
#include "../../simdebug.h"
#include "../haus_besch.h"
#include "../intro_dates.h"
#include "../obj_node_info.h"
#include "building_reader.h"
#include "../../network/pakset_info.h"


obj_besch_t * tile_reader_t::read_node(FILE *fp, obj_node_info_t &node)
{
	ALLOCA(char, besch_buf, node.size);

	haus_tile_besch_t *desc = new haus_tile_besch_t();

	// Hajo: Read data
	fread(besch_buf, node.size, 1, fp);

	char * p = besch_buf;

	// Hajo: old versions of PAK files have no version stamp.
	// But we know, the highest bit was always cleared.
	const uint16 v = decode_uint16(p);
	const int version = (v & 0x8000)!=0 ? v&0x7FFF : 0;

	if(version == 2) {
//  DBG_DEBUG("tile_reader_t::read_node()","version=1");
		// Versioned node, version 1
		desc->phasen = (uint8)decode_uint16(p);
		desc->index = decode_uint16(p);
		desc->seasons = decode_uint8(p);
		desc->haus = NULL;
	}
	else if(version == 1) {
//  DBG_DEBUG("tile_reader_t::read_node()","version=1");
		// Versioned node, version 1
		desc->phasen = (uint8)decode_uint16(p);
		desc->index = decode_uint16(p);
		desc->seasons = 1;
		desc->haus = NULL;
	}
	else {
		// skip the pointer ...
		p += 2;
		desc->phasen = (uint8)decode_uint16(p);
		desc->index = decode_uint16(p);
		desc->seasons = 1;
		desc->haus = NULL;
	}
	DBG_DEBUG("tile_reader_t::read_node()","phasen=%i index=%i seasons=%i", desc->phasen, desc->index, desc->seasons );

	return desc;
}




void building_reader_t::register_obj(obj_besch_t *&data)
{
	haus_besch_t *desc = static_cast<haus_besch_t *>(data);

	if(  desc->utype == haus_besch_t::fabrik  ) {
		if(  desc->enables == 0  ) {
			// this stuff is just for compatibility
			if(  strcmp("Oelbohrinsel",desc->get_name())==0  ) {
				desc->enables = 1|2|4;
			}
			else if(  strcmp("fish_swarm",desc->get_name())==0  ) {
				desc->enables = 4;
			}
		}
	}

	if(  desc->utype == haus_besch_t::weitere  &&  desc->enables == 0x80  ) {
		// this stuff is just for compatibility
		size_t checkpos = strlen(desc->get_name());
		desc->enables = 0;
		// before station buildings were identified by their name ...
		if(  strcmp("BusStop",desc->get_name()+checkpos-7)==0  ) {
			desc->utype = haus_besch_t::generic_stop;
			desc->extra_data = road_wt;
			desc->enables = 1;
		}
		if(  strcmp("CarStop",desc->get_name()+checkpos-7)==0  ) {
			desc->utype = haus_besch_t::generic_stop;
			desc->extra_data = road_wt;
			desc->enables = 4;
		}
		else if(  strcmp("TrainStop",desc->get_name()+checkpos-9)==0  ) {
			desc->utype = haus_besch_t::generic_stop;
			desc->extra_data = track_wt;
			desc->enables = 1|4;
		}
		else if(  strcmp("ShipStop",desc->get_name()+checkpos-8)==0  ) {
			desc->utype = haus_besch_t::dock;
			desc->extra_data = water_wt;
			desc->enables = 1|4;
		}
		else if(  strcmp("ChannelStop",desc->get_name()+checkpos-11)==0  ) {
			desc->utype = haus_besch_t::generic_stop;
			desc->extra_data = water_wt;
			desc->enables = 1|4;
		}
		else if(  strcmp("PostOffice",desc->get_name()+checkpos-10)==0  ) {
			desc->utype = haus_besch_t::generic_extension;
			desc->extra_data = 0;
			desc->enables = 2;
		}
		else if(  strcmp("StationBlg",desc->get_name()+checkpos-10)==0  ) {
			desc->utype = haus_besch_t::generic_extension;
			desc->extra_data = 0;
			desc->enables = 1|4;
		}
	}
	// now old style depots ...
	else if(  desc->utype==haus_besch_t::weitere  ) {
		size_t checkpos = strlen(desc->get_name());
		if(  strcmp("AirDepot",desc->get_name()+checkpos-8)==0  ) {
			desc->utype = haus_besch_t::depot;
			desc->extra_data = (uint16)air_wt;
		}
		else if(  strcmp("TrainDepot",desc->get_name())==0  ) {
			desc->utype = haus_besch_t::depot;
			desc->extra_data = (uint16)track_wt;
		}
		else if(  strcmp("TramDepot",desc->get_name())==0  ) {
			desc->utype = haus_besch_t::depot;
			desc->extra_data = (uint16)tram_wt;
		}
		else if(  strcmp("MonorailDepot",desc->get_name())==0  ) {
			desc->utype = haus_besch_t::depot;
			desc->extra_data = (uint16)monorail_wt;
		}
		else if(  strcmp("CarDepot",desc->get_name())==0  ) {
			desc->utype = haus_besch_t::depot;
			desc->extra_data = (uint16)road_wt;
		}
		else if(  strcmp("ShipDepot",desc->get_name())==0  ) {
			desc->utype = haus_besch_t::depot;
			desc->extra_data = (uint16)water_wt;
		}
	}
	// and finally old stations ...
	else if(  desc->get_utyp()>=haus_besch_t::bahnhof  &&  desc->get_utyp()<=haus_besch_t::lagerhalle) {
		// compability stuff
		static uint16 old_to_new_waytype[16] = { track_wt, road_wt, road_wt, water_wt, water_wt, air_wt, monorail_wt, 0, track_wt, road_wt, road_wt, 0 , water_wt, air_wt, monorail_wt, 0 };
		desc->extra_data = desc->utype<=haus_besch_t::monorail_geb ? old_to_new_waytype[desc->utype-haus_besch_t::bahnhof] : 0;
		if(  desc->utype!=haus_besch_t::dock  ) {
			desc->utype = desc->utype<haus_besch_t::bahnhof_geb ? haus_besch_t::generic_stop : haus_besch_t::generic_extension;
		}
	}

	// allowed layouts are 1,2,4,8,16, where 8,16 is reserved for stations
	uint8 l = desc->utype == haus_besch_t::generic_stop ? 16 : 4;
	while (l > 0) {
		if ((desc->layouts & l) != 0  &&  (desc->layouts != l)) {
			dbg->error( "building_reader_t::register_obj()", "Building %s has %i layouts (illegal) => set to %i", desc->get_name(), desc->layouts, l );
			desc->layouts = l;
			break;
		}
		l >>= 1;
	}

	if(  desc->allow_underground == 255  ) {
		// only old stops were allowed underground
		desc->allow_underground = desc->utype==haus_besch_t::generic_stop ? 2 : 0;
	}

	if (hausbauer_t::register_desc(desc)) {
		DBG_DEBUG("building_reader_t::register_obj", "Loaded '%s'", desc->get_name());

		// do not calculate checksum of factory, will be done in factory_reader_t
		if(  desc->utype != haus_besch_t::fabrik  ) {
			checksum_t *chk = new checksum_t();
			desc->calc_checksum(chk);
			pakset_info_t::append(desc->get_name(), chk);
		}
	}
}


bool building_reader_t::successfully_loaded() const
{
	return hausbauer_t::alles_geladen();
}


obj_besch_t * building_reader_t::read_node(FILE *fp, obj_node_info_t &node)
{
	ALLOCA(char, besch_buf, node.size);

	haus_besch_t *desc = new haus_besch_t();

	// Hajo: Read data
	fread(besch_buf, node.size, 1, fp);

	char * p = besch_buf;
	// Hajo: old versions of PAK files have no version stamp.
	// But we know, the highest bit was always cleared.
	const uint16 v = decode_uint16(p);
	const int version = (v & 0x8000)!=0 ? v&0x7FFF : 0;

	if(version == 8) {
		// Versioned node, version 8
		// station price, maintenance and capacity added
		desc->gtyp      = (gebaeude_t::typ)decode_uint8(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint8(p);
		desc->level     = decode_uint16(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint8(p);
		desc->allowed_climates = (climate_bits)decode_uint16(p);
		desc->enables   = decode_uint8(p);
		desc->flags     = (haus_besch_t::flag_t)decode_uint8(p);
		desc->chance    = decode_uint8(p);
		desc->intro_date    = decode_uint16(p);
		desc->obsolete_date = decode_uint16(p);
		desc->animation_time = decode_uint16(p);
		desc->capacity  = decode_uint16(p);
		desc->maintenance = decode_sint32(p);
		desc->price     = decode_sint32(p);
		desc->allow_underground = decode_uint8(p);
	}
	else if(version == 7) {
		// Versioned node, version 7
		// underground mode added
		desc->gtyp      = (gebaeude_t::typ)decode_uint8(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint8(p);
		desc->level     = decode_uint16(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint8(p);
		desc->allowed_climates = (climate_bits)decode_uint16(p);
		desc->enables   = decode_uint8(p);
		desc->flags     = (haus_besch_t::flag_t)decode_uint8(p);
		desc->chance    = decode_uint8(p);
		desc->intro_date    = decode_uint16(p);
		desc->obsolete_date = decode_uint16(p);
		desc->animation_time = decode_uint16(p);
		desc->allow_underground = decode_uint8(p);
	}
	else if(version == 5  ||  version==6) {
		// Versioned node, version 5 or 6  (only level logic is different)
		// animation intervall in ms added
		desc->gtyp      = (gebaeude_t::typ)decode_uint8(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint8(p);
		desc->level     = decode_uint16(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint8(p);
		desc->allowed_climates = (climate_bits)decode_uint16(p);
		desc->enables   = decode_uint8(p);
		desc->flags     = (haus_besch_t::flag_t)decode_uint8(p);
		desc->chance    = decode_uint8(p);
		desc->intro_date    = decode_uint16(p);
		desc->obsolete_date = decode_uint16(p);
		desc->animation_time = decode_uint16(p);
	}
	else if(version == 4) {
		// Versioned node, version 4
		// climates and seasons added
		desc->gtyp      = (gebaeude_t::typ)decode_uint8(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint8(p);
		desc->level     = decode_uint16(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint8(p);
		desc->allowed_climates = (climate_bits)decode_uint16(p);
		desc->enables   = decode_uint8(p);
		desc->flags     = (haus_besch_t::flag_t)decode_uint8(p);
		desc->chance    = decode_uint8(p);
		desc->intro_date    = decode_uint16(p);
		desc->obsolete_date = decode_uint16(p);
		desc->animation_time = 300;
	}
	else if(version == 3) {
		// Versioned node, version 3
		desc->gtyp      = (gebaeude_t::typ)decode_uint8(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint8(p);
		desc->level     = decode_uint16(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint8(p);
		desc->allowed_climates   =  (climate_bits)0xFFFE; // all but water
		desc->enables   = decode_uint8(p);
		desc->flags     = (haus_besch_t::flag_t)decode_uint8(p);
		desc->chance    = decode_uint8(p);
		desc->intro_date    = decode_uint16(p);
		desc->obsolete_date = decode_uint16(p);
		desc->animation_time = 300;
	}
	else if(version == 2) {
		// Versioned node, version 2
		desc->gtyp      = (gebaeude_t::typ)decode_uint8(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint8(p);
		desc->level     = decode_uint16(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint8(p);
		desc->allowed_climates   =  (climate_bits)0xFFFE; // all but water
		desc->enables   = 0x80;
		desc->flags     = (haus_besch_t::flag_t)decode_uint8(p);
		desc->chance    = decode_uint8(p);
		desc->intro_date    = decode_uint16(p);
		desc->obsolete_date = decode_uint16(p);
		desc->animation_time = 300;
	}
	else if(version == 1) {
		// Versioned node, version 1
		desc->gtyp      = (gebaeude_t::typ)decode_uint8(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint8(p);
		desc->level     = decode_uint16(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint8(p);
		desc->allowed_climates   =  (climate_bits)0xFFFE; // all but water
		desc->enables   = 0x80;
		desc->flags     = (haus_besch_t::flag_t)decode_uint8(p);
		desc->chance    = decode_uint8(p);

		desc->intro_date    = DEFAULT_INTRO_DATE*12;
		desc->obsolete_date = DEFAULT_RETIRE_DATE*12;
		desc->animation_time = 300;
	}
	else {
		// old node, version 0
		desc->gtyp      = (gebaeude_t::typ)v;
		decode_uint16(p);
		desc->utype     = (haus_besch_t::utyp)decode_uint32(p);
		desc->level     = decode_uint32(p);
		desc->extra_data= decode_uint32(p);
		desc->size.x = decode_uint16(p);
		desc->size.y = decode_uint16(p);
		desc->layouts   = decode_uint32(p);
		desc->allowed_climates   =  (climate_bits)0xFFFE; // all but water
		desc->enables   = 0x80;
		desc->flags     = (haus_besch_t::flag_t)decode_uint32(p);
		desc->chance    = 100;

		desc->intro_date    = DEFAULT_INTRO_DATE*12;
		desc->obsolete_date = DEFAULT_RETIRE_DATE*12;
		desc->animation_time = 300;
	}
	// there are additional nodes for cursor/icon
	if(  node.children > 2+desc->size.x*desc->size.y*desc->layouts  ) {
		desc->flags |= haus_besch_t::FLAG_HAS_CURSOR;
	}

	// correct old station buildings ...
	if(  version<=3  &&  (desc->utype >= haus_besch_t::bahnhof  ||  desc->utype == haus_besch_t::fabrik  ||  desc->utype == haus_besch_t::depot)  &&  desc->level==0  ) {
		DBG_DEBUG("building_reader_t::read_node()","old station building -> set level to 4");
		desc->level = 4;
	}
	else if(  version<=5  &&  (desc->utype == haus_besch_t::fabrik  ||  desc->utype == haus_besch_t::depot)  ) {
		desc->level ++;
		DBG_DEBUG("building_reader_t::read_node()","old station building -> increment level by one to %i", desc->level );
	}

	if(  version<=6  ) {
		// only stops were allowed underground
		desc->allow_underground = 255;
	}

	if(  version<=7  ) {
		// capacity, maintenance and price were set from level
		desc->capacity = desc->level * 32;
		desc->maintenance = COST_MAGIC;
		desc->price = COST_MAGIC;
	}

	if (desc->level == 65535) {
		desc->level = 0;	// apparently wrong level
		dbg->warning("building_reader_t::read_node()","level was 65535, intended was probably 0 => changed." );
	}

	DBG_DEBUG("building_reader_t::read_node()",
		"version=%d"
		" gtyp=%d"
		" utyp=%d"
		" level=%d"
		" extra_data=%d"
		" size.x=%d"
		" size.y=%d"
		" layouts=%d"
		" enables=%x"
		" flags=%d"
		" chance=%d"
		" climates=%X"
		" anim=%d"
		" intro=%d"
		" retire=%d",
		version,
		desc->gtyp,
		desc->utype,
		desc->level,
		desc->extra_data,
		desc->size.x,
		desc->size.y,
		desc->layouts,
		desc->enables,
		desc->flags,
		desc->chance,
		desc->allowed_climates,
		desc->animation_time,
		desc->intro_date,
		desc->obsolete_date
	);

	return desc;

}
