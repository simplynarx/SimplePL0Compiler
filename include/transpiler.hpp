#pragma once

#include <iostream>
#include <fstream>

class Transpiler {
    public:
        Transpiler();
        ~Transpiler();
        friend class Parser;


    private:
        std::ofstream out_file;

        void t_const(std::string token);
        void t_num(std::string token);
        void t_semicolon();
        void t_comma();
        void t_const_assignment(std::string token);
        void t_var(std::string token);
        void t_ident(std::string token);
        void t_procedure(std::string token);
        void t_var_assignment(std::string token);
        void t_end();
        void t_call(std::string token);
        void t_input(std::string token);
        void t_output(std::string token);
};
