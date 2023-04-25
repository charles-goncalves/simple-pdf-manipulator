#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>

#include "perlFunction.h"

PerlFunction::PerlFunction (string name){
    char empty[1] = "", scriptName[13] = "functions.pl";
    char *argv[] = {empty, scriptName};

    functionName = name;

    perl = perl_alloc();
    perl_construct(perl);

    perl_parse(perl, xs_init, 2, argv, NULL);
}

PerlFunction::~PerlFunction (){
    perl_destruct(perl);
    perl_free(perl);
}

const char *PerlFunction::getFunctionName() {
    return functionName.c_str();
}

string PerlFunction::run() {
    int nReturned = 0; 
    string validation = validateArguments();

    if (!validation.empty()) {
        return validation;
    }   

    dSP;  
    ENTER;        
    SAVETMPS;

    PUSHMARK(sp);

    setPerlArguments(sp);

    if(getOutputLength()) {
        XPUSHs(sv_2mortal(newSVpv(getOutput(), getOutputLength())));
    }

    PUTBACK;

    nReturned = perl_call_pv (getFunctionName(), G_SCALAR);

    SPAGAIN;

    if(nReturned == 1) {
        return string(POPp);
    }

    return string("FAILED\n");
}

void PerlFunction::setFileNameA(string filename) {
    fileNameA = filename;
}

void PerlFunction::setFileNameB(string filename) {
    fileNameB = filename;
}

void PerlFunction::setOutput(string filename) {
    output = filename;
}

void PerlFunction::setBegin(size_t b) {
    begin = b;
}

void PerlFunction::setEnd(size_t e) {
    end = e;
}

const char *PerlFunction::getFileNameA() {
    return fileNameA.c_str();
}

const char *PerlFunction::getFileNameB() {
    return fileNameB.c_str();
}

const char *PerlFunction::getOutput() {
    return output.c_str();
}

size_t PerlFunction::getBegin() {
    return begin;
}

size_t PerlFunction::getEnd() {
    return end;
}

size_t PerlFunction::getFileNameALength() {
    return fileNameA.length();
}

size_t PerlFunction::getFileNameBLength() {
    return fileNameB.length();
}

size_t PerlFunction::getOutputLength() {
    return output.length();
}

AppendPDF::AppendPDF(): PerlFunction("append_pdf") {}

string AppendPDF::validateArguments() {
    if (!getFileNameALength() || !getFileNameBLength()){
        return string("Set the two files names first\n");
    }

    return string("");
}

void AppendPDF::setPerlArguments(SV **&sp) {
    XPUSHs(sv_2mortal(newSVpv(getFileNameA(), getFileNameALength())));
    XPUSHs(sv_2mortal(newSVpv(getFileNameB(), getFileNameBLength())));
}

ExtractPagesFromPDF::ExtractPagesFromPDF(): PerlFunction("extract_pages_pdf") {}

string ExtractPagesFromPDF::validateArguments() {
    if (!getFileNameALength()){
        return string("Set the file name first\n");
    }

    if (getBegin() > getEnd()) {
        size_t aux = getBegin();
        setBegin(getEnd());
        setEnd(aux);
    }

    return string("");
}

void ExtractPagesFromPDF::setPerlArguments(SV **&sp) {
    XPUSHs(sv_2mortal(newSVpv(getFileNameA(), getFileNameALength())));
    XPUSHs(sv_2mortal(newSViv(getBegin())));
    XPUSHs(sv_2mortal(newSViv(getEnd())));
}

DeletePagesFromPDF::DeletePagesFromPDF(): PerlFunction("delete_pages_pdf") {}

string DeletePagesFromPDF::validateArguments() {
    if (!getFileNameALength()){
        return string("Set the file name first\n");
    }

    if (getBegin() > getEnd()) {
        size_t aux = getBegin();
        setBegin(getEnd());
        setEnd(aux);
    }

    return string("");
}

void DeletePagesFromPDF::setPerlArguments(SV **&sp) {
    XPUSHs(sv_2mortal(newSVpv(getFileNameA(), getFileNameALength())));
    XPUSHs(sv_2mortal(newSViv(getBegin())));
    XPUSHs(sv_2mortal(newSViv(getEnd())));
}

ExtractTextFromPDF::ExtractTextFromPDF(): PerlFunction("extract_text_pdf") {}

string ExtractTextFromPDF::validateArguments() {
    if (!getFileNameALength()){
        return string("Set the file name first\n");
    }

    return string("");
}

void ExtractTextFromPDF::setPerlArguments(SV **&sp) {
    XPUSHs(sv_2mortal(newSVpv(getFileNameA(), getFileNameALength())));
}

ClearPDFAnnotations::ClearPDFAnnotations(): PerlFunction("clear_annotations_pdf") {}

string ClearPDFAnnotations::validateArguments() {
    if (!getFileNameALength()){
        return string("Set the file name first\n");
    }

    return string("");
}

void ClearPDFAnnotations::setPerlArguments(SV **&sp) {
    XPUSHs(sv_2mortal(newSVpv(getFileNameA(), getFileNameALength())));
}

EXTERN_C void
xs_init(pTHX)
{
    static const char file[] = __FILE__;
    dXSUB_SYS;
    PERL_UNUSED_CONTEXT;

    newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}

