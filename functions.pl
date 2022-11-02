#!/usr/bin/perl
# package perl_functions;

use strict;
use warnings;
use CAM::PDF;


sub append_pdf {
    my ($fileName1, $fileName2, $output) = @_;
    my $pdf1 = CAM::PDF->new($fileName1) || die "$CAM::PDF::errstr\n";
    my $pdf2 = CAM::PDF->new($fileName2) || die "$CAM::PDF::errstr\n";
    my $nPages = $pdf2->numPages();
    my $outputName;

    if(!$pdf1->canModify() || !$pdf2->canCopy()) {
        die "The file has no permission for append\n";
    }

    $pdf1->appendPDF($pdf2);
    $pdf1->cleanoutput($output || $fileName1) || die "$CAM::PDF::errstr\n";

    if ($output) {
        $nPages += $pdf1->numPages();
    } 

    $outputName = $output || $fileName1;

    return "SUCCESS!\n$nPages pages appended to $outputName.\n";
}

sub extract_pages_pdf {
    my ($fileName1, $begin, $end, $output) = @_;
    my $pdf = CAM::PDF->new($fileName1) || die "$CAM::PDF::errstr\n";
    my $outputName;

    if(!$pdf->canCopy()) {
        die "The file has no permission for extraction\n";
    }

    if ($pdf->numPages() < $end) {
        $end = $pdf->numPages();
    }

    $pdf->extractPages($begin..$end);
    $pdf->cleanoutput($output || $fileName1) || die "$CAM::PDF::errstr\n";

    $outputName = $output || $fileName1;

    return "SUCCESS!\nPages $begin to $end extracted to $outputName.\n";
}

sub delete_pages_pdf {
    my ($fileName1, $begin, $end, $output) = @_;
    my $pdf = CAM::PDF->new($fileName1) || die "$CAM::PDF::errstr\n";
    my $outputName = "";

    if(!$pdf->canModify()) {
        die "The file has no permission for manipulation\n";
    }

    if ($pdf->numPages() < $end) {
        $end = $pdf->numPages();
    }

    $pdf->deletePages($begin..$end);
    $pdf->cleanoutput($output || $fileName1) || die "$CAM::PDF::errstr\n";

    if($output) {
        $outputName = "Result saved into $output.";
    }

    return "SUCCESS!\nPages $begin to $end deleted from $fileName1. $outputName\n";
}

sub extract_text_pdf {
    my ($fileName1) = @_;
    my $pdf = CAM::PDF->new($fileName1) || die "$CAM::PDF::errstr\n";
    my $outputString = "";

    if(!$pdf->canCopy()) {
        die "The file has no permission for extraction\n";
    }

    foreach(1..$pdf->numPages()) {
        $outputString .= $pdf->getPageText($_);
    }

    if($outputString eq "") {
        return "No text can be extracted from $fileName1.";
    }

    return $outputString;
}

sub clear_annotations_pdf {
    my ($fileName1, $output) = @_;
    my $pdf = CAM::PDF->new($fileName1) || die "$CAM::PDF::errstr\n";
    my $outputName = "";

    if(!$pdf->canModify()) {
        die "The file has no permission for manipulation\n";
    }

    $pdf->clearAnnotations();
    $pdf->cleanoutput($output || $fileName1) || die "$CAM::PDF::errstr\n";

    if($output) {
        $outputName = "Result saved into $output.";
    }

    return "SUCCESS!\nAnnotations removed from $fileName1. $outputName\n";
}
 
