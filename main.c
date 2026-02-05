#include <stdio.h>
#include <string.h>
#include "view.h"
#include "edit.h"
#include "types.h"

//validate the arguments
int validate_args(char *argv[]){
    if(strcmp(argv[1],"-v")==0){
        if(argv[2]==NULL){
            return unsupported;
        }
        else{
            return view;
        }
    }
    else if(strcmp(argv[1],"-e")==0){
        if(argv[2]==NULL || argv[3]==NULL || argv[4]==NULL){
            return unsupported;
        }
        else{
            return edit;
        }
    }
    else if(strcmp(argv[1],"--help")==0){
        return help;
    }
    else{
        return unsupported;
    }
    
}

int main(int argc,char *argv[])
{
    if(argc<2){
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE :\n");
        printf("To help please pass like: ./a.out --help\n");
        printf("To view please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c <new_name> <mp3filename>\n");
        return 0;
    }
    else{
        int ret=validate_args(argv);
        if(ret==view){
            MP3_view(argv);
        }
        else if(ret==edit){
            char *id=NULL;
            if(strcmp(argv[2],"-t")==0){
                id="TIT2";
            }
            else if(strcmp(argv[2],"-a")==0){
                id="TPE1";
            }
            else if(strcmp(argv[2],"-A")==0){
                id="TALB";
            }
            else if(strcmp(argv[2],"-y")==0){
                id="TYER";
            }
            else if(strcmp(argv[2],"-m")==0){
                id="TCON";
            }
            else if(strcmp(argv[2],"-c")==0){
                id="COMM";
            }
            else{
                return unsupported;
            }
            MP3_edit(id,argv[3],argv[4]);
        }
        else if(ret==help){
            printf ("INFO: Help Menu for Tag Reader and Editor:\n");
            printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
            printf ("INFO: For Editing the Tags -> ./mp3_tag_reader -e <modifier> \"New_Value\" <file_name.mp3>\n");
            printf ("INFO: Modifier Functions:\n");
            printf("1. -v -> to view mp3 file contents\n");
            printf("2. -e -> to edit mp3 file contents\n");
            printf("   2.1. -t -> Modifies a Title tag\n"
                   "   2.2. -a -> Modifies an Artist tag\n"
                   "   2.3. -A -> Modifies an Album tag\n"
                   "   2.4. -y -> Modifies a Year tag\n"
                   "   2.5. -m -> Modifies a Content tag\n"
                   "   2.6. -c -> Modifies a Comment tag\n");
        }
        else if(ret==unsupported){
            printf ("ERROR: Unsupported Operation.\n");
            printf ("INFO: Use \"./a.out --help\" for Help menu.\n");
        }
    }
    return 0;
}

