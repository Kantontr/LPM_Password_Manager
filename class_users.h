#ifndef CLASS_USERS_H
#define CLASS_USERS_H
#include "utility.h"

class Class_Passwords{
public:


    Class_Passwords(){
        //path_to_vault = getenv("appdata");
        //path_to_vault += "\\KantonLPM\\Password_Manager";
        //file_path = path_to_vault;
        file_path = "pswd.txt";
        file_path_enc = path_to_vault;
        file_path_enc = "pswd(enc).txt";
        active_users=0;
        users = new struct_users[1000];

    }
        std::string path_to_vault;
        std::string password;
        std::string file_size;
        std::string random_iv;
        std::string file_path;
        std::string file_path_enc;

        int active_users;

        struct struct_users{
            std::string name;
            std::string login;
            std::string password;
        };
        struct_users *users;


        inline bool file_enc_dec(std::string flag,std::string password){


            std::string command;

            command = "LPM_FileEncrypter.exe ";

            if(flag == "-e"){
                command += file_path;
            }
            else if(flag=="-d"){
                command += file_path_enc;
            }

            command += " ";
            command += flag;
            command += " -s ";
            command+= password;

            std::cout<<"Executing command: "<<std::endl;
            std::cout<<command<<std::endl;


            system(command.c_str());

            if(LPM_file_exist(file_path) && flag == "-d"){
                std::cout<<"dec: Operacja udana! "<<std::endl;
                return true;
            }
            else if (LPM_file_exist(file_path_enc) && flag == "-e")
            {
                std::cout<<"Enc: Operacja udana! "<<std::endl;
                return true;
            }
            else {
                std::cout<<"Enc/dec: Error operacji"<<std::endl;
                return false;
            }


        }


        inline bool load_passwords(){


            if(LPM_file_exist(file_path_enc)){
                std::cout<<"Pswd::Load_passwords: Decrypting file!"<<std::endl;
                file_enc_dec("-d",password);
            }else return false;


            if(!(LPM_file_exist(file_path)))return false;

            active_users=0;


            std::ifstream infile(file_path);
            std::string line;

            while (std::getline(infile, line))
            {
                users[active_users].name = line;
                std::getline(infile, line);
                users[active_users].login = line;
                std::getline(infile, line);
                users[active_users].password = line;
                active_users+=1;
            }
            infile.close();
            //active_users-=1;

            if(LPM_file_exist(file_path)){
                std::cout<<"Pswd::Load_passwords: Encrypting file!"<<std::endl;
                file_enc_dec("-e",password);
            }

            std::cout<<"Password::Load_Users: Wczytano! Nb of users: "<<active_users<<std::endl;
            //file_enc_dec("-e",password);
            return true;

        }



        inline bool save_to_file(){


            std::cout<<"Password::Save_to_File: Zaczynam zapis!"<<std::endl;
            FILE *fp;
            if((fp = fopen(file_path.c_str(),"w"))!=NULL) {
                for (int i = 0; i < active_users; i++)
                {
                    fprintf(fp, "%s\n", users[i].name.c_str());
                    fprintf(fp, "%s\n", users[i].login.c_str());
                    fprintf(fp, "%s\n", users[i].password.c_str());

                }
                fclose(fp);
                std::cout<<"Password::save_to_file: Zmiany zostaly wprowadzone do pliku!"<<std::endl;
                std::cout<<"Pswd::save_to_file: Encrypting file!"<<std::endl;
                file_enc_dec("-e",password);

                return true;

            }
            else {
                std::cout<<"Password::Save_to_File: Nie mozna otworzyc pliku!"<<std::endl;
                return false;
            }


        }

        inline bool add_user(std::string new_name,std::string new_login,std::string new_password){

            std::cout<<"Password::add_user: Dodaje: "<<new_name<<" "<<new_login<<" "<<new_password<<"active users: "<<active_users<<std::endl;
            users[active_users].name = new_name;
            users[active_users].login = new_login;
            users[active_users].password = new_password;
            active_users+=1;

            return save_to_file();

        }

        inline bool remove_user(int id_z_listy){

            if(active_users==1){
                active_users=0;
                return save_to_file();
            }

            for (int i=id_z_listy;i<active_users;i++){
                if(i+1 < active_users){
                    users[i].name = users[i+1].name;
                    users[i].login = users[i+1].login;
                    users[i].password = users[i+1].password;
                }
            }
            active_users-=1;
            return save_to_file();

        }


};

inline Class_Passwords *Passwords = new Class_Passwords;
#endif // CLASS_USERS_H
