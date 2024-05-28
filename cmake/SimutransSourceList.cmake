target_sources(simutrans PRIVATE
		src/simutrans/builder/brueckenbauer.cc
		src/simutrans/builder/fabrikbauer.cc
		src/simutrans/builder/goods_manager.cc
		src/simutrans/builder/hausbauer.cc
		src/simutrans/builder/tree_builder.cc
		src/simutrans/builder/tunnelbauer.cc
		src/simutrans/builder/vehikelbauer.cc
		src/simutrans/builder/wegbauer.cc
		src/simutrans/dataobj/crossing_logic.cc
		src/simutrans/dataobj/environment.cc
		src/simutrans/dataobj/freelist.cc
		src/simutrans/dataobj/gameinfo.cc
		src/simutrans/dataobj/height_map_loader.cc
		src/simutrans/dataobj/koord.cc
		src/simutrans/dataobj/koord3d.cc
		src/simutrans/dataobj/loadsave.cc
		src/simutrans/dataobj/marker.cc
		src/simutrans/dataobj/objlist.cc
		src/simutrans/dataobj/pakset_manager.cc
		src/simutrans/dataobj/pakset_downloader.cc
		src/simutrans/dataobj/powernet.cc
		src/simutrans/dataobj/records.cc
		src/simutrans/dataobj/rect.cc
		src/simutrans/dataobj/ribi.cc
		src/simutrans/dataobj/route.cc
		src/simutrans/dataobj/scenario.cc
		src/simutrans/dataobj/schedule.cc
		src/simutrans/dataobj/settings.cc
		src/simutrans/dataobj/sve_cache.cc
		src/simutrans/dataobj/tabfile.cc
		src/simutrans/dataobj/translator.cc
		src/simutrans/descriptor/bridge_desc.cc
		src/simutrans/descriptor/building_desc.cc
		src/simutrans/descriptor/factory_desc.cc
		src/simutrans/descriptor/goods_desc.cc
		src/simutrans/descriptor/ground_desc.cc
		src/simutrans/descriptor/image.cc
		src/simutrans/descriptor/obj_base_desc.cc
		src/simutrans/descriptor/reader/bridge_reader.cc
		src/simutrans/descriptor/reader/building_reader.cc
		src/simutrans/descriptor/reader/citycar_reader.cc
		src/simutrans/descriptor/reader/crossing_reader.cc
		src/simutrans/descriptor/reader/factory_reader.cc
		src/simutrans/descriptor/reader/good_reader.cc
		src/simutrans/descriptor/reader/ground_reader.cc
		src/simutrans/descriptor/reader/groundobj_reader.cc
		src/simutrans/descriptor/reader/image_reader.cc
		src/simutrans/descriptor/reader/imagelist2d_reader.cc
		src/simutrans/descriptor/reader/imagelist_reader.cc
		src/simutrans/descriptor/reader/obj_reader.cc
		src/simutrans/descriptor/reader/pedestrian_reader.cc
		src/simutrans/descriptor/reader/roadsign_reader.cc
		src/simutrans/descriptor/reader/root_reader.cc
		src/simutrans/descriptor/reader/sim_reader.cc
		src/simutrans/descriptor/reader/skin_reader.cc
		src/simutrans/descriptor/reader/sound_reader.cc
		src/simutrans/descriptor/reader/text_reader.cc
		src/simutrans/descriptor/reader/tree_reader.cc
		src/simutrans/descriptor/reader/tunnel_reader.cc
		src/simutrans/descriptor/reader/vehicle_reader.cc
		src/simutrans/descriptor/reader/way_obj_reader.cc
		src/simutrans/descriptor/reader/way_reader.cc
		src/simutrans/descriptor/reader/xref_reader.cc
		src/simutrans/descriptor/sound_desc.cc
		src/simutrans/descriptor/tunnel_desc.cc
		src/simutrans/descriptor/vehicle_desc.cc
		src/simutrans/descriptor/way_desc.cc
		src/simutrans/display/font.cc
		src/simutrans/display/simview.cc
		src/simutrans/display/viewport.cc
		src/simutrans/freight_list_sorter.cc
		src/simutrans/ground/boden.cc
		src/simutrans/ground/brueckenboden.cc
		src/simutrans/ground/fundament.cc
		src/simutrans/ground/grund.cc
		src/simutrans/ground/monorailboden.cc
		src/simutrans/ground/tunnelboden.cc
		src/simutrans/ground/wasser.cc
		src/simutrans/gui/components/gui_aligned_container.cc
		src/simutrans/gui/components/gui_building.cc
		src/simutrans/gui/components/gui_button.cc
		src/simutrans/gui/components/gui_button_to_chart.cc
		src/simutrans/gui/components/gui_chart.cc
		src/simutrans/gui/components/gui_colorbox.cc
		src/simutrans/gui/components/gui_combobox.cc
		src/simutrans/gui/components/gui_component.cc
		src/simutrans/gui/components/gui_container.cc
		src/simutrans/gui/components/gui_convoiinfo.cc
		src/simutrans/gui/components/gui_divider.cc
		src/simutrans/gui/components/gui_fixedwidth_textarea.cc
		src/simutrans/gui/components/gui_flowtext.cc
		src/simutrans/gui/components/gui_image.cc
		src/simutrans/gui/components/gui_image_list.cc
		src/simutrans/gui/components/gui_label.cc
		src/simutrans/gui/components/gui_map_preview.cc
		src/simutrans/gui/components/gui_numberinput.cc
		src/simutrans/gui/components/gui_obj_view.cc
		src/simutrans/gui/components/gui_schedule.cc
		src/simutrans/gui/components/gui_scrollbar.cc
		src/simutrans/gui/components/gui_scrolled_list.cc
		src/simutrans/gui/components/gui_scrollpane.cc
		src/simutrans/gui/components/gui_speedbar.cc
		src/simutrans/gui/components/gui_tab_panel.cc
		src/simutrans/gui/components/gui_textarea.cc
		src/simutrans/gui/components/gui_textinput.cc
		src/simutrans/gui/components/gui_timeinput.cc
		src/simutrans/gui/components/gui_waytype_tab_panel.cc
		src/simutrans/gui/components/gui_world_view.cc
		src/simutrans/gui/ai_option.cc
		src/simutrans/gui/ai_selector.cc
		src/simutrans/gui/banner.cc
		src/simutrans/gui/base_info.cc
		src/simutrans/gui/baum_edit.cc
		src/simutrans/gui/city_info.cc
		src/simutrans/gui/citybuilding_edit.cc
		src/simutrans/gui/citylist_frame.cc
		src/simutrans/gui/citylist_stats.cc
		src/simutrans/gui/climates.cc
		src/simutrans/gui/chat_frame.cc
		src/simutrans/gui/convoi_detail.cc
		src/simutrans/gui/convoi_filter_frame.cc
		src/simutrans/gui/convoi_frame.cc
		src/simutrans/gui/convoi_info.cc
		src/simutrans/gui/convoy_item.cc
		src/simutrans/gui/curiosity_edit.cc
		src/simutrans/gui/curiositylist_frame.cc
		src/simutrans/gui/curiositylist_stats.cc
		src/simutrans/gui/depot_frame.cc
		src/simutrans/gui/depotlist_frame.cc
		src/simutrans/gui/display_settings.cc
		src/simutrans/gui/enlarge_map_frame.cc
		src/simutrans/gui/extend_edit.cc
		src/simutrans/gui/fabrik_info.cc
		src/simutrans/gui/factory_chart.cc
		src/simutrans/gui/factory_edit.cc
		src/simutrans/gui/factorylist_frame.cc
		src/simutrans/gui/factorylist_stats.cc
		src/simutrans/gui/goods_frame.cc
		src/simutrans/gui/goods_stats.cc
		src/simutrans/gui/ground_info.cc
		src/simutrans/gui/groundobj_edit.cc
		src/simutrans/gui/gui_frame.cc
		src/simutrans/gui/gui_theme.cc
		src/simutrans/gui/halt_info.cc
		src/simutrans/gui/halt_list_filter_frame.cc
		src/simutrans/gui/halt_list_frame.cc
		src/simutrans/gui/halt_list_stats.cc
		src/simutrans/gui/headquarter_info.cc
		src/simutrans/gui/help_frame.cc
		src/simutrans/gui/jump_frame.cc
		src/simutrans/gui/kennfarbe.cc
		src/simutrans/gui/label_info.cc
		src/simutrans/gui/labellist_frame.cc
		src/simutrans/gui/labellist_stats.cc
		src/simutrans/gui/line_item.cc
		src/simutrans/gui/line_management_gui.cc
		src/simutrans/gui/load_relief_frame.cc
		src/simutrans/gui/loadfont_frame.cc
		src/simutrans/gui/loadsave_frame.cc
		src/simutrans/gui/map_frame.cc
		src/simutrans/gui/message_frame.cc
		src/simutrans/gui/message_option.cc
		src/simutrans/gui/message_stats.cc
		src/simutrans/gui/messagebox.cc
		src/simutrans/gui/minimap.cc
		src/simutrans/gui/money_frame.cc
		src/simutrans/gui/obj_info.cc
		src/simutrans/gui/optionen.cc
		src/simutrans/gui/pakinstaller.cc
		src/simutrans/gui/pakselector.cc
		src/simutrans/gui/password_frame.cc
		src/simutrans/gui/player_frame.cc
		src/simutrans/gui/player_ranking_frame.cc
		src/simutrans/gui/privatesign_info.cc
		src/simutrans/gui/savegame_frame.cc
		src/simutrans/gui/scenario_frame.cc
		src/simutrans/gui/scenario_info.cc
		src/simutrans/gui/schedule_list.cc
		src/simutrans/gui/script_tool_frame.cc
		src/simutrans/gui/server_frame.cc
		src/simutrans/gui/settings_frame.cc
		src/simutrans/gui/settings_stats.cc
		src/simutrans/gui/signal_info.cc
		src/simutrans/gui/signal_spacing.cc
		src/simutrans/gui/simwin.cc
		src/simutrans/gui/sound_frame.cc
		src/simutrans/gui/sprachen.cc
		src/simutrans/gui/station_building_select.cc
		src/simutrans/gui/themeselector.cc
		src/simutrans/gui/tool_selector.cc
		src/simutrans/gui/trafficlight_info.cc
		src/simutrans/gui/vehiclelist_frame.cc
		src/simutrans/gui/welt.cc
		src/simutrans/io/classify_file.cc
		src/simutrans/io/raw_image.cc
		src/simutrans/io/raw_image_bmp.cc
		src/simutrans/io/raw_image_png.cc
		src/simutrans/io/raw_image_ppm.cc
		src/simutrans/io/rdwr/adler32_stream.cc
		src/simutrans/io/rdwr/bzip2_file_rdwr_stream.cc
		src/simutrans/io/rdwr/compare_file_rd_stream.cc
		src/simutrans/io/rdwr/raw_file_rdwr_stream.cc
		src/simutrans/io/rdwr/rdwr_stream.cc
		src/simutrans/io/rdwr/zlib_file_rdwr_stream.cc
		src/simutrans/network/checksum.cc
		src/simutrans/network/memory_rw.cc
		src/simutrans/network/network.cc
		src/simutrans/network/network_address.cc
		src/simutrans/network/network_cmd.cc
		src/simutrans/network/network_cmd_ingame.cc
		src/simutrans/network/network_cmd_scenario.cc
		src/simutrans/network/network_cmp_pakset.cc
		src/simutrans/network/network_file_transfer.cc
		src/simutrans/network/network_packet.cc
		src/simutrans/network/network_socket_list.cc
		src/simutrans/network/pakset_info.cc
		src/simutrans/obj/baum.cc
		src/simutrans/obj/bruecke.cc
		src/simutrans/obj/crossing.cc
		src/simutrans/obj/depot.cc
		src/simutrans/obj/field.cc
		src/simutrans/obj/gebaeude.cc
		src/simutrans/obj/groundobj.cc
		src/simutrans/obj/label.cc
		src/simutrans/obj/leitung2.cc
		src/simutrans/obj/pillar.cc
		src/simutrans/obj/roadsign.cc
		src/simutrans/obj/signal.cc
		src/simutrans/obj/simobj.cc
		src/simutrans/obj/tunnel.cc
		src/simutrans/obj/way/kanal.cc
		src/simutrans/obj/way/maglev.cc
		src/simutrans/obj/way/monorail.cc
		src/simutrans/obj/way/narrowgauge.cc
		src/simutrans/obj/way/runway.cc
		src/simutrans/obj/way/schiene.cc
		src/simutrans/obj/way/strasse.cc
		src/simutrans/obj/way/weg.cc
		src/simutrans/obj/wayobj.cc
		src/simutrans/obj/wolke.cc
		src/simutrans/obj/zeiger.cc
		src/simutrans/old_blockmanager.cc
		src/simutrans/player/ai.cc
		src/simutrans/player/ai_goods.cc
		src/simutrans/player/ai_passenger.cc
		src/simutrans/player/ai_scripted.cc
		src/simutrans/player/finance.cc
		src/simutrans/player/simplay.cc
		src/simutrans/revision.h
		src/simutrans/script/api/api_city.cc
		src/simutrans/script/api/api_command.cc
		src/simutrans/script/api/api_const.cc
		src/simutrans/script/api/api_control.cc
		src/simutrans/script/api/api_convoy.cc
		src/simutrans/script/api/api_factory.cc
		src/simutrans/script/api/api_gui.cc
		src/simutrans/script/api/api_halt.cc
		src/simutrans/script/api/api_include.cc
		src/simutrans/script/api/api_line.cc
		src/simutrans/script/api/api_map_objects.cc
		src/simutrans/script/api/api_obj_desc.cc
		src/simutrans/script/api/api_obj_desc_base.cc
		src/simutrans/script/api/api_pathfinding.cc
		src/simutrans/script/api/api_player.cc
		src/simutrans/script/api/api_scenario.cc
		src/simutrans/script/api/api_schedule.cc
		src/simutrans/script/api/api_settings.cc
		src/simutrans/script/api/api_simple.cc
		src/simutrans/script/api/api_tiles.cc
		src/simutrans/script/api/api_world.cc
		src/simutrans/script/api/export_desc.cc
		src/simutrans/script/api/get_next.cc
		src/simutrans/script/api_class.cc
		src/simutrans/script/api_function.cc
		src/simutrans/script/api_param.cc
		src/simutrans/script/dynamic_string.cc
		src/simutrans/script/export_objs.cc
		src/simutrans/script/script.cc
		src/simutrans/script/script_loader.cc
		src/simutrans/script/script_tool_manager.cc
		src/simutrans/simachievements.cc
		src/simutrans/simconvoi.cc
		src/simutrans/simdebug.cc
		src/simutrans/simevent.cc
		src/simutrans/simfab.cc
		src/simutrans/simhalt.cc
		src/simutrans/siminteraction.cc
		src/simutrans/simintr.cc
		src/simutrans/simio.cc
		src/simutrans/simline.cc
		src/simutrans/simlinemgmt.cc
		src/simutrans/simloadingscreen.cc
		src/simutrans/simmain.cc
		src/simutrans/simmem.cc
		src/simutrans/simmesg.cc
		src/simutrans/simskin.cc
		src/simutrans/simsound.cc
		src/simutrans/simticker.cc
		src/simutrans/simware.cc
		src/simutrans/sys/simsys.cc
		src/simutrans/tool/simmenu.cc
		src/simutrans/tool/simtool-scripted.cc
		src/simutrans/tool/simtool.cc
		src/simutrans/utils/cbuffer.cc
		src/simutrans/utils/checklist.cc
		src/simutrans/utils/csv.cc
		src/simutrans/utils/log.cc
		src/simutrans/utils/searchfolder.cc
		src/simutrans/utils/sha1.cc
		src/simutrans/utils/sha1_hash.cc
		src/simutrans/utils/simrandom.cc
		src/simutrans/utils/simstring.cc
		src/simutrans/utils/simthread.cc
		src/simutrans/utils/unicode.cc
		src/simutrans/vehicle/air_vehicle.cc
		src/simutrans/vehicle/movingobj.cc
		src/simutrans/vehicle/pedestrian.cc
		src/simutrans/vehicle/rail_vehicle.cc
		src/simutrans/vehicle/road_vehicle.cc
		src/simutrans/vehicle/simroadtraffic.cc
		src/simutrans/vehicle/vehicle.cc
		src/simutrans/vehicle/vehicle_base.cc
		src/simutrans/vehicle/water_vehicle.cc
		src/simutrans/world/placefinder.cc
		src/simutrans/world/simcity.cc
		src/simutrans/world/simplan.cc
		src/simutrans/world/simworld.cc
		src/simutrans/world/surface.cc
		src/simutrans/world/terraformer.cc
		src/squirrel/sq_extensions.cc
		src/squirrel/sqstdlib/sqstdaux.cc
		src/squirrel/sqstdlib/sqstdblob.cc
		src/squirrel/sqstdlib/sqstdio.cc
		src/squirrel/sqstdlib/sqstdmath.cc
		src/squirrel/sqstdlib/sqstdrex.cc
		src/squirrel/sqstdlib/sqstdstream.cc
		src/squirrel/sqstdlib/sqstdstring.cc
		src/squirrel/sqstdlib/sqstdsystem.cc
		src/squirrel/squirrel/sqapi.cc
		src/squirrel/squirrel/sqbaselib.cc
		src/squirrel/squirrel/sqclass.cc
		src/squirrel/squirrel/sqcompiler.cc
		src/squirrel/squirrel/sqdebug.cc
		src/squirrel/squirrel/sqfuncstate.cc
		src/squirrel/squirrel/sqlexer.cc
		src/squirrel/squirrel/sqmem.cc
		src/squirrel/squirrel/sqobject.cc
		src/squirrel/squirrel/sqstate.cc
		src/squirrel/squirrel/sqtable.cc
		src/squirrel/squirrel/sqvm.cc
)
