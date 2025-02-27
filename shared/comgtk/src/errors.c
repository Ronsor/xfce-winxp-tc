#include <glib.h>
#include <gtk/gtk.h>

#include "errors.h"
#include "msgbox.h"

//
// GLIB BOILERPLATE
//
G_DEFINE_QUARK(wintc-general-error-quark, wintc_general_error)

//
// PUBLIC FUNCTIONS
//
void wintc_display_error_and_clear(
    GError** error
)
{
    wintc_messagebox_show(
        NULL,
        (*error)->message,
        "",
        GTK_BUTTONS_OK,
        GTK_MESSAGE_ERROR
    );

    g_clear_error(error);
}

void wintc_log_error_and_clear(
    GError** error
)
{
    g_message("%s", (*error)->message);

    g_clear_error(error);
}

void wintc_nice_error_and_clear(
    GError** error
)
{
    const gchar* message = NULL;

    if ((*error)->domain == WINTC_GENERAL_ERROR)
    {
        switch ((*error)->code)
        {
            case WINTC_GENERAL_ERROR_NOTIMPL:
                message = "Sorry, this feature is not implemented yet!";
                break;
        }
    }

    if (message != NULL)
    {
        wintc_messagebox_show(
            NULL,
            message,
            "",
            GTK_BUTTONS_OK,
            GTK_MESSAGE_ERROR
        );

        g_clear_error(error);
    }
    else
    {
        wintc_display_error_and_clear(error);
    }
}
