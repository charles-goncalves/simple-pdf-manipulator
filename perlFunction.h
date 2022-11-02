/* Universidade Federal do Rio de Janeiro 
 * Disciplina: Linguagens de Programação - Prof: Miguel Elias
 * Trabalho Final 2020/2
 * Alunos:
 *  Charles Alexandre Pereira Gonçalves
 *  Fabio do Nascimento Oliveira
 */
#include <iostream>
#include <vector>

#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>

#include <string>

using namespace std;

EXTERN_C void xs_init (pTHX);

EXTERN_C void boot_CAM__PDF (pTHX_ CV* cv);
EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

class PerlFunction {

    public:
        PerlFunction(string);
        ~PerlFunction();

        string run();

        virtual string validateArguments() = 0;
        virtual void setPerlArguments(SV **&) = 0;

        const char *getFunctionName();

        void setFileNameA(string);
        void setFileNameB(string);
        void setOutput(string);
        void setBegin(size_t);
        void setEnd(size_t);
        const char *getFileNameA();
        const char *getFileNameB();
        const char *getOutput();
        size_t getBegin();
        size_t getEnd();
        size_t getFileNameALength();
        size_t getFileNameBLength();
        size_t getOutputLength();

    private:
        PerlInterpreter *perl;
        string functionName;

        string fileNameA;
        string fileNameB;
        string output;
        size_t begin, end;
};


class AppendPDF: public PerlFunction {
    public:
        AppendPDF();

        virtual void setPerlArguments(SV **&);
        virtual string validateArguments();

};

class ExtractPagesFromPDF: public PerlFunction {
    public:
        ExtractPagesFromPDF();

        virtual void setPerlArguments(SV **&);
        virtual string validateArguments();
        
};

class DeletePagesFromPDF: public PerlFunction {
    public:
        DeletePagesFromPDF();

        virtual void setPerlArguments(SV **&);
        virtual string validateArguments();
        
};

class ExtractTextFromPDF: public PerlFunction {
    public:
        ExtractTextFromPDF();

        virtual void setPerlArguments(SV **&);
        virtual string validateArguments();
        
};

class ClearPDFAnnotations: public PerlFunction {
    public:
        ClearPDFAnnotations();

        virtual void setPerlArguments(SV **&);
        virtual string validateArguments();
        
};
