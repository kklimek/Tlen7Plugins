#ifndef _TLEN_EXPORT_H_
#define _TLEN_EXPORT_H_

#ifdef _WIN32

#	ifdef tlen_core_EXPORTS
#		define __tlen_core__ __declspec(dllexport)
#	else
#		define __tlen_core__ __declspec(dllimport)
#	endif

#	ifdef tlen_data_EXPORTS
#		define __tlen_data__ __declspec(dllexport)
#	else
#		define __tlen_data__ __declspec(dllimport)
#	endif

#	ifdef tlen_plugin_EXPORTS
#		define __tlen_plugin__ __declspec(dllexport)
#	else
#		define __tlen_plugin__ __declspec(dllimport)
#	endif

#	ifdef tlen_xml_EXPORTS
#		define __tlen_xml__ __declspec(dllexport)
#	else
#		define __tlen_xml__ __declspec(dllimport)
#	endif

#	ifdef tlen_audio_EXPORTS
#		define __tlen_audio__ __declspec(dllexport)
#	else
#		define __tlen_audio__ __declspec(dllimport)
#	endif


#	ifdef tlen_network_EXPORTS
#		define __tlen_network__ __declspec(dllexport)
#	else
#		define __tlen_network__ __declspec(dllimport)
#	endif

#	ifdef tlen_settings_EXPORTS
#		define __tlen_settings__ __declspec(dllexport)
#	else
#		define __tlen_settings__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_pubdir_search_EXPORTS
#		define __tlen_gui_pubdir_search__ __declspec(dllexport)
#	else
#		define __tlen_gui_pubdir_search__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_accounts_tab_EXPORTS
#		define __tlen_gui_accounts_tab__ __declspec(dllexport)
#	else
#		define __tlen_gui_accounts_tab__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_plugins_tab_EXPORTS
#		define __tlen_gui_plugins_tab__ __declspec(dllexport)
#	else
#		define __tlen_gui_plugins_tab__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_notifications_tab_EXPORTS
#		define __tlen_gui_notifications_tab__ __declspec(dllexport)
#	else
#		define __tlen_gui_notifications_tab__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_roster_filters_tab_EXPORTS
#		define __tlen_gui_roster_filters_tab__ __declspec(dllexport)
#	else
#		define __tlen_gui_roster_filters_tab__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_buddy_dialog_EXPORTS
#		define __tlen_gui_buddy_dialog__ __declspec(dllexport)
#	else
#		define __tlen_gui_buddy_dialog__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_chat_manager_EXPORTS
#		define __tlen_gui_chat_manager__ __declspec(dllexport)
#	else
#		define __tlen_gui_chat_manager__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_chat_window_EXPORTS
#		define __tlen_gui_chat_window__ __declspec(dllexport)
#	else
#		define __tlen_gui_chat_window__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_main_window_EXPORTS
#		define __tlen_gui_main_window__ __declspec(dllexport)
#	else
#		define __tlen_gui_main_window__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_message_box_EXPORTS
#		define __tlen_gui_message_box__ __declspec(dllexport)
#	else
#		define __tlen_gui_message_box__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_editor_EXPORTS
#		define __tlen_gui_editor__ __declspec(dllexport)
#	else
#		define __tlen_gui_editor__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_plugin_EXPORTS
#		define __tlen_gui_plugin__ __declspec(dllexport)
#	else
#		define __tlen_gui_plugin__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_roster_EXPORTS
#		define __tlen_gui_roster__ __declspec(dllexport)
#	else
#		define __tlen_gui_roster__ __declspec(dllimport)
#	endif

#	ifdef tlen_roster_EXPORTS
#		define __tlen_roster__ __declspec(dllexport)
#	else
#		define __tlen_roster__ __declspec(dllimport)
#	endif

#	ifdef tlen_video_EXPORTS
#		define __tlen_video__ __declspec(dllexport)
#	else
#		define __tlen_video__ __declspec(dllimport)
#	endif


#	ifdef tlen_gui_avatar_EXPORTS
#		define __tlen_gui_avatar__ __declspec(dllexport)
#	else
#		define __tlen_gui_avatar__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_registration_wizard_EXPORTS
#		define __tlen_gui_registration_wizard__ __declspec(dllexport)
#	else
#		define __tlen_gui_registration_wizard__ __declspec(dllimport)
#	endif


#	ifdef tlen_gui_settings_manager_EXPORTS
#		define __tlen_gui_settings_manager__ __declspec(dllexport)
#	else
#		define __tlen_gui_settings_manager__ __declspec(dllimport)
#	endif

#	ifdef tlen_protocol_plugin_EXPORTS
#		define __tlen_protocol_plugin__ __declspec(dllexport)
#	else
#		define __tlen_protocol_plugin__ __declspec(dllimport)
#	endif

#	ifdef tlen_protocol_plugin_p2p_EXPORTS
#		define __tlen_protocol_plugin_p2p__ __declspec(dllexport)
#	else
#		define __tlen_protocol_plugin_p2p__ __declspec(dllimport)
#	endif

#	ifdef tlen_protocol_plugin_p2p_voip_EXPORTS
#		define __tlen_protocol_plugin_p2p_voip__ __declspec(dllexport)
#	else
#		define __tlen_protocol_plugin_p2p_voip__ __declspec(dllimport)
#	endif

#	ifdef tlen_protocol_plugin_p2p_file_EXPORTS
#		define __tlen_protocol_plugin_p2p_file__ __declspec(dllexport)
#	else
#		define __tlen_protocol_plugin_p2p_file__ __declspec(dllimport)
#	endif

#	ifdef tlen_uigenerator_EXPORTS
#		define __tlen_uigenerator__ __declspec(dllexport)
#	else
#		define __tlen_uigenerator__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_notification_EXPORTS
#		define __tlen_gui_notify__ __declspec(dllexport)
#	else
#		define __tlen_gui_notify__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_context_menu_EXPORTS
#		define __tlen_gui_context_menu__ __declspec(dllexport)
#	else
#		define __tlen_gui_context_menu__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_events_EXPORTS
#		define __tlen_gui_events__ __declspec(dllexport)
#	else
#		define __tlen_gui_events__ __declspec(dllimport)
#	endif

#	ifdef tlen_application_EXPORTS
#		define __tlen_application__ __declspec(dllexport)
#	else
#		define __tlen_application__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_message_box_EXPORTS
#		define __tlen_gui_message_box__ __declspec(dllexport)
#	else
#		define __tlen_gui_message_box__ __declspec(dllimport)
#	endif

#	ifdef tlen_archive_EXPORTS
#		define __tlen_archive__ __declspec(dllexport)
#	else
#		define __tlen_archive__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_widgets_EXPORTS
#		define __tlen_gui_widgets__ __declspec(dllexport)
#	else
#		define __tlen_gui_widgets__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_transfers_EXPORTS
#		define __tlen_gui_transfers__ __declspec(dllexport)
#	else
#		define __tlen_gui_transfers__ __declspec(dllimport)
#	endif

#	ifdef tlen_message_logger_EXPORTS
#		define __tlen_message_logger__ __declspec(dllexport)
#	else
#		define __tlen_message_logger__ __declspec(dllimport)
#	endif


#	ifdef tlen_protocol_plugin_p2p_EXPORTS
#		define __tlen_protocol_plugin_p2p__ __declspec(dllexport)
#	else
#		define __tlen_protocol_plugin_p2p__ __declspec(dllimport)
#	endif

#	ifdef tlen_protocol_plugin_p2p_voip_EXPORTS
#		define __tlen_protocol_plugin_p2p_voip__ __declspec(dllexport)
#	else
#		define __tlen_protocol_plugin_p2p_voip__ __declspec(dllimport)
#	endif

#	ifdef tlen_protocol_plugin_p2p_file_EXPORTS
#		define __tlen_protocol_plugin_p2p_file__ __declspec(dllexport)
#	else
#		define __tlen_protocol_plugin_p2p_file__ __declspec(dllimport)
#	endif

#	ifdef tlen_uigenerator_EXPORTS
#		define __tlen_ui_generator__ __declspec(dllexport)
#	else
#		define __tlen_ui_generator__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_settings_manager_EXPORTS
#		define __tlen_gui_settings_manager__ __declspec(dllexport)
#	else
#		define __tlen_gui_settings_manager__ __declspec(dllimport)
#	endif

#	ifdef tlen_db_module_EXPORTS
#		define __db_module__ __declspec(dllexport)
#	else
#		define __db_module__ __declspec(dllimport)
#	endif

#	ifdef tlen_archive_backend_EXPORTS
#		define __tlen_archive_backend__ __declspec(dllexport)
#	else
#		define __tlen_archive_backend__ __declspec(dllimport)
#	endif

#	ifdef tlen_archive_EXPORTS
#		define __tlen_archive__ __declspec(dllexport)
#	else
#		define __tlen_archive__ __declspec(dllimport)
#	endif

#	ifdef tlen_archive_module_EXPORTS
#		define __archive_module__ __declspec(dllexport)
#	else
#		define __archive_module__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_plugins_tab_EXPORTS
#		define __tlen_gui_plugins_tab__ __declspec(dllexport)
#	else
#		define __tlen_gui_plugins_tab__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_archive_EXPORTS
#		define __tlen_gui_archive__ __declspec(dllexport)
#	else
#		define __tlen_gui_archive__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_login_window_EXPORTS
#		define __tlen_gui_login_window__ __declspec(dllexport)
#	else
#		define __tlen_gui_login_window__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_status_window_EXPORTS
#		define __tlen_gui_status_window__ __declspec(dllexport)
#	else
#		define __tlen_gui_status_window__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_tooltip_EXPORTS
#		define __tlen_gui_tooltip__ __declspec(dllexport)
#	else
#		define __tlen_gui_tooltip__ __declspec(dllimport)
#	endif

#	ifdef tlen_gemius_EXPORTS
#		define __tlen_gemius__ __declspec(dllexport)
#	else
#		define __tlen_gemius__ __declspec(dllimport)
#	endif

#	ifdef tlen_language_EXPORTS
#		define __tlen_language__ __declspec(dllexport)
#	else
#		define __tlen_language__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_utils_EXPORTS
#		define __tlen_gui_utils__ __declspec(dllexport)
#	else
#		define __tlen_gui_utils__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_extensions_EXPORTS
#		define __tlen_gui_extensions__ __declspec(dllexport)
#	else
#		define __tlen_gui_extensions__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_roster_filter_EXPORTS
#		define __tlen_gui_roster_filter__ __declspec(dllexport)
#	else
#		define __tlen_gui_roster_filter__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_profiles_EXPORTS
#		define __tlen_gui_profiles__ __declspec(dllexport)
#	else
#		define __tlen_gui_profiles__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_tray_EXPORTS
#		define __tlen_gui_tray__ __declspec(dllexport)
#	else
#		define __tlen_gui_tray__ __declspec(dllimport)
#	endif

#	ifdef tlen_gui_accounts_tab_EXPORTS
#		define __tlen_accounts_tab__ __declspec(dllexport)
#	else
#		define __tlen_accounts_tab__ __declspec(dllimport)
#	endif

#else

#	define __tlen_core__
#	define __tlen_data__
#	define __tlen_plugin__
#	define __tlen_xml__
#	define __tlen_network__
#	define __tlen_settings__
#	define __tlen_gui_accounts_tab__
#	define __tlen_gui_plugins_tab__
#	define __tlen_gui_notifications_tab__
#	define __tlen_gui_buddy_dialog__
#	define __tlen_gui_chat_manager__
#	define __tlen_gui_chat_window__
#	define __tlen_gui_main_window__
#	define __tlen_gui_message_box__
#	define __tlen_gui_plugin__
#	define __tlen_gui_roster__
#	define __tlen_roster__
#	define __tlen_video__
#	define __tlen_gui_avatar__
#	define __tlen_gui_settings_manager__
#	define __tlen_protocol_plugin__
#	define __tlen_protocol_plugin_p2p__
#	define __tlen_protocol_plugin_p2p_voip__
#	define __tlen_protocol_plugin_p2p_file__
#	define __tlen_uigenerator__
#	define __tlen_gui_notify__
#	define __tlen_gui_context_menu__
#	define __tlen_gui_events__
#	define __tlen_archive__
#	define __tlen_application__
#	define __tlen_gui_message_box__
#	define __tlen_gui_widgets__
#	define __tlen_gui_transfers__
#	define __tlen_protocol_plugin_p2p__
#	define __tlen_protocol_plugin_p2p_voip__
#	define __tlen_protocol_plugin_p2p_file__
#	define __tlen_gui_pubdir_search__
#	define __tlen_message_logger__
#	define __tlen_audio__
#	define __tlen_ui_generator__
#	define __tlen_gui_settings_manager__
#	define __db_module__
#	define __tlen_archive_backend__
#	define __tlen_archive__
#	define __archive_module__
#	define __tlen_gui_plugins_tab__
#	define __tlen_gui_archive__
#	define __tlen_gui_registration_wizard__
#	define __tlen_gui_login_window__
#	define __tlen_gui_status_window__
#	define __tlen_gui_editor__
#	define __tlen_gui_tooltip__
#	define __tlen_gemius__
#	define __tlen_language__
#	define __tlen_gui_utils__
#	define __tlen_gui_extensions__
#	define __tlen_gui_roster_filter__
#	define __tlen_gui_roster_filters_tab__
#	define __tlen_gui_profiles__
#	define __tlen_gui_tray__
#	define __tlen_accounts_tab__
#endif


#endif	// _TLEN_EXPORT_H_
