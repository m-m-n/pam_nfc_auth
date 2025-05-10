#define _GNU_SOURCE
#include <security/pam_ext.h>
#include <security/pam_modules.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int __attribute__((unused)) flags,
                                   int __attribute__((unused)) argc,
                                   const char __attribute__((unused)) * *argv)
{
    int retval;
    const char *user;
    char *nfc_reader_cmd;

    if (pam_get_user(pamh, &user, NULL) != PAM_SUCCESS) {
        return PAM_AUTH_ERR;
    }

    if (asprintf(&nfc_reader_cmd, "/usr/local/bin/nfc-reader --timeout=30 --allow-list-file=/usr/local/etc/allowed-list.txt --user=%s", user) == -1) {
        return PAM_AUTH_ERR;
    }

    retval = system(nfc_reader_cmd);
    free(nfc_reader_cmd);

    if (retval == 0) {
        return PAM_SUCCESS;
    }

    return PAM_AUTH_ERR;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t __attribute__((unused)) * pamh,
                              int __attribute__((unused)) flags,
                              int __attribute__((unused)) argc,
                              const char __attribute__((unused)) * *argv)
{
    return PAM_SUCCESS;
}

#ifdef PAM_STATIC
struct pam_module _pam_nfc_auth_modstruct = {
  "pam_nfc_auth",
  pam_sm_authenticate,
  pam_sm_setcred,
  NULL,
  NULL,
  NULL,
  NULL,
};
#endif
