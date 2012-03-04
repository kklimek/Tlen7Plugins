#ifndef __TLEN_PLUGIN_DEFINES_H__
#define __TLEN_PLUGIN_DEFINES_H__

/**
 * Core signals
 */
#define ACC_REMOVED			"account_removed"
#define ACC_DISABLED			"account_disabled"
#define ACC_ENABLED			"account_enabled"
#define PLUGIN_LOADED			"plugin_loaded"
#define PLUGIN_UNLOADED			"plugin_unloaded"
#define LOADED_PROTOCOL			"protocol_loaded"
#define UNLOADED_PROTOCOL		"protocol_unloaded"
#define MSG_ABOUT_TO_SEND		"message_about_to_send"
#define CONFERENCE_MSG_ABOUT_TO_SEND	"conference_message_about_to_send"
#define MSG_PRIVATE_ABOUT_TO_SEND 	"conference_private_message_about_to_send"
#define CONFERENCE_LEAVE 		"conference_leave"
#define MSG_READ			"message_read"
#define POST_NOTIFICATION		"post_notification"
#define UPDATE_PLUGIN_GUI  		"update_plugin_gui"
#define REGISTER_ACCOUNT		"register_account"
#define APP_INITIALIZED			"app_initialized"
#define APP_QUITTING			"app_quitting"


/**
 * Gui signals
 */
#define CONTEXT_MENU_REQUESTED		"context_menu_requested"
#define	CHAT_WINDOW_CREATED		"chat_window_created"

/**
 * Default notifications
 */

#define MESSAGE_RECEIVED_NOTIFY		"message_received"
#define MESSAGE_RECEIVED_INIT_NOTIFY	"message_received_initial"
#define MESSAGE_RECEIVED_BG_NOTIFY	"message_received_background"
#define MESSAGE_SENT_NOTIFY		"message_sent"

#define CONF_MESSAGE_RECEIVED_NOTIFY 	"conf_message_received"
#define CONF_MESSAGE_RECEIVED_BG_NOTIFY "conf_message_bg_received"

#define INFO_NOTIFY			"info_notify"
#define ERROR_NOTIFY			"error_notify"
#define EMAIL_NOTIFY			"email_notify"
#define ALERT_SENT_NOTIFY		"alert_sent_notify"
#define ALERT_RECEIVED_NOTIFY		"alert_received_notify"

#define TYPING_STARTED			"typing_started_notify"
#define TYPING_STOPED			"typing_stoped_notify"

#define BUDDY_WENT_OFFLINE_NOTIFY	"buddy_went_offline"
#define BUDDY_WENT_AWAY_NOTIFY		"buddy_went_away"
#define BUDDY_CONNECTED_NOTIFY		"buddy_connected"
#define BUDDY_CHANGED_STATUS_NOTIFY	"buddy_changed_status"

#define LOGGEDIN_NOTIFY			"logged_in"

#endif

