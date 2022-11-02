/* Universidade Federal do Rio de Janeiro 
 * Disciplina: Linguagens de Programação - Prof: Miguel Elias
 * Trabalho Final 2020/2
 * Autor:
 *  Charles Alexandre Pereira Gonçalves
 */
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "perlFunction.h"

#define ARGUMENT_ERROR  1
#define OK  0

using namespace std;

void printUsage(){
cout << "Simple PDF Manipulator\n" << endl;
cout << "usage: ./pdfm [-o <path>] -a BASE SUP" << endl;
cout << "or: ./pdfm [-o <path>] -e BEGIN END BASE" << endl;
cout << "or: ./pdfm [-o <path>] -d BEGIN END BASE" << endl;
cout << "or: ./pdfm [-o <path>] -t BASE" << endl;
cout << "or: ./pdfm [-o <path>] -c BASE" << endl;
cout << endl;
cout << "options:" << endl;
cout << "\t-o <path>\t\toutput path" << endl;
cout << "\t-a\t\t\tAppend PDF: appends SUP into BASE" << endl;
cout << "\t-e\t\t\tExtract from PDF: extract pages BEGIN to END from BASE" << endl;
cout << "\t-d\t\t\tDelete pages of PDF: delete pages BEGIN to END sequentially from BASE" << endl;
cout << "\t-t\t\t\tExtract text from PDF: extract all possible from BASE (note: may have no extraction at all)" << endl;
cout << "\t-c\t\t\tClean Annotations in PDF: erase all annotations in BASE" << endl;
cout << endl;
}

bool validatePDFFile(string filename) {
    string extension = filename.substr(filename.length() - 4);

    if(extension == ".pdf" || extension == ".PDF")
        return true;
    
    return false;
}

int main(int argc, char **argv) {
    int option;
    char *validation;
    bool textOutputToFile = false;
    bool extract = false;
    fstream outputFile;
    string output(""), filenameA(""), filenameB(""), returnedValue;
    size_t begin, end;
    PerlFunction *function;

    if(argc < 3){
        printUsage();
        exit(ARGUMENT_ERROR);
    }
    
    while ((option = getopt(argc, argv, "o:aedtc")) != -1) {
        switch(option) {
            case 'o':
                output = optarg;

                if(!validatePDFFile(output)) {
                    output.append(".pdf");
                }
            continue;

            case 'a':
                if(argc - optind != 2){
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }

                filenameA = argv[optind++];
                filenameB = argv[optind];
                if(!validatePDFFile(filenameA) || !validatePDFFile(filenameB)) {
                    cout << "Invalid argument: BASE and SUP must be a PDF file\n" << endl;
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }
                function = new AppendPDF();
            break;

            case 'e':
                extract = true;
            case 'd':
                if(argc - optind != 3){
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }

                begin = (size_t) strtoul(argv[optind++], &validation, 10);
                if(*validation != '\0'){
                    cout << "Invalid argument: BEGIN must be a integer\n" << endl;
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }

                end = (size_t) strtoul(argv[optind++], &validation, 10);
                if(*validation != '\0'){
                    cout << "Invalid argument: END must be a integer\n" << endl;
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }

                filenameA = argv[optind++];
                if(!validatePDFFile(filenameA)) {
                    cout << "Invalid argument: BASE must be a PDF file\n" << endl;
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }

                if (option == 'e')
                    function = new ExtractPagesFromPDF(); 
                else
                    function = new DeletePagesFromPDF();
            break;

            case 't':
                textOutputToFile = true;
            case 'c':
                if(argc - optind != 1){
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }

                filenameA = argv[optind];
                if(!validatePDFFile(filenameA)) {
                    cout << "Invalid argument: BASE must be a PDF file\n" << endl;
                    printUsage();
                    exit(ARGUMENT_ERROR);
                }

                if (option == 't')
                    function = new ExtractTextFromPDF(); 
                else
                    function = new ClearPDFAnnotations();
            break;
            default:
                printUsage();
            break;
        }
    }

    function->setFileNameA(filenameA);
    function->setFileNameB(filenameB);
    function->setOutput(output);
    function->setBegin(begin);
    function->setEnd(end);

    returnedValue = function->run();

    if(textOutputToFile && output.length()){
        output.append(".txt");
        outputFile.open(output, ios::out | ios::trunc);

        if(outputFile.is_open()){
            outputFile << returnedValue;
        }
    }

    cout << returnedValue << endl;

    return 0;    
}