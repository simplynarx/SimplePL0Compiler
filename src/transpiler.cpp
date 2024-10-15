#include <transpiler.hpp>

Transpiler::Transpiler() {
    out_file.open("out.c");

    if(!out_file) {
        std::cerr << "Error: could not open transpilation file)"
                  << std::endl;
        exit(1);
    }

    out_file << "#include <stdio.h>\n\n";
}

Transpiler::~Transpiler() {
    out_file << "int main(void) {\n\n";
    out_file << "printf(\"\\n\");\n";
    out_file << "return 0;";
    out_file << "\n}";
    out_file.close();
}

void Transpiler::t_const(std::string token) {
    out_file << "const long " << token << " = ";
}

void Transpiler::t_num(std::string token) {
    out_file << token;
}

void Transpiler::t_semicolon() {
    out_file << ";\n";
}

void Transpiler::t_comma() {
    out_file << ", ";
}

void Transpiler::t_const_assignment(std::string token) {
    out_file << token << " = ";
}

void Transpiler::t_var(std::string token) {
    out_file << "long " << token;
}

void Transpiler::t_ident(std::string token) {
    out_file << token;
}

void Transpiler::t_procedure(std::string token) {
    out_file << "void " << token << "(void) {\n";
}

void Transpiler::t_var_assignment(std::string token) {
    out_file << token << " = ";
}

void Transpiler::t_end() {
    out_file << "}\n\n";
}

void Transpiler::t_call(std::string token) {
    out_file << token << "(void)";
}

void Transpiler::t_input(std::string token) {
    out_file << "scanf(\"%li\", &" << token << ")";
}

void Transpiler::t_output(std::string token) {
    out_file << "printf(\"%li\", " << token << ")";
}
