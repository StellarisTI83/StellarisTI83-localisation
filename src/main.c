#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "local_keys.h"
#include "generic_lists.h"
#include "appvar.h"
#include "parsing.h"

void delete_list(GenericList *liste){
    int i = 0;
    configStruct *config;
    config = GenericCellGet(liste, i);
    while(config) {
        printf("%d, %s\n", config->key, config->value);
        free(config);
        i++;
        config = GenericCellGet(liste, i);
    }
    GenericListFree(liste);
    printf("\n");
}

int main() {
    FILE *translation_fr;
    FILE *translation_en;

    GenericList *liste_fr = GenericListCreate();
    GenericList *liste_en = GenericListCreate();

    translation_fr = fopen("config files/translation_fr.txt", "r");
    translation_en = fopen("config files/translation_en.txt", "r");
    
    
    config_file_parse(translation_fr, liste_fr);
    config_file_parse(translation_en, liste_en);

    appvar_ecrire("lcFR.8xv", "lcFR", "French translation for Stellaris", liste_fr);
    appvar_ecrire("lcEN.8xv", "lcEN", "English translation for Stellaris", liste_en);

    fclose(translation_fr);
    fclose(translation_en);

    delete_list(liste_fr);
    delete_list(liste_en);

    return 0;
}