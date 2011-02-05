#include <libxslt/xslt.h>
#include <libexslt/exslt.h>
#include "SWFFile.h"
#include "swft.h"
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <dirent.h>

using namespace SWF;

bool quiet = false;
bool verbose = false;
bool dump = false;
bool nonet = false;
const char *swf_encoding = "UTF-8";
const char *internal_stylesheet = NULL;

#include "simple.h"

void usage() {
}

// helper func
xsltStylesheetPtr xsltParseStylesheetMemory( const char *buffer, int size ) {
	xmlDocPtr doc = xmlParseMemory( buffer, size );
	if( !doc ) return NULL;
	xsltStylesheetPtr ret = xsltParseStylesheetDoc( doc );
	return ret;
}

int swfmill_xml2swf( int argc, char *argv[] ) {
	const char *infile = NULL, *outfile = "stdout";
	bool success = false;
	FILE *in_fp=0, *out_fp=0;
	bool std_in = false, std_out = false;
	const char *filename;
	xsltStylesheetPtr transform = NULL;
	
	File input;
	int size;
	Context ctx;
	xmlDocPtr doc = NULL, doc2;

	// parse filenames
	if( argc < 1 || argc > 2 ) {
		usage();
		goto fail;
	}
	infile = argv[0];
	if( argc>1 ) outfile = argv[1];
	
	// open files
	std_in = !strncmp( infile, "stdin", 5 );
	std_out = !strncmp( outfile, "stdout", 6 );
	in_fp = std_in ? stdin : fopen( infile, "rb" );
	if( !in_fp ) {
		fprintf(stderr,"ERROR: could not open file %s for reading\n", infile?infile:"stdin" );
		goto fail;
	}
	
	if( !quiet ) fprintf(stderr,"Reading from %s\n", infile );
	
	// setup context
	ctx.debugTrace = verbose;
	ctx.quiet = quiet;

	// setup encoding conversion.
	if (strcmp(swf_encoding, "UTF-8")) {
		ctx.convertEncoding = true;
		ctx.swf_encoding = swf_encoding;
	}

	{
		filename = std_in ? "-" : infile ;
		doc = xmlParseFile( filename );
		if( !doc ) {
			fprintf( stderr, "ERROR: input document %s could not be read.\n", infile );
			goto fail;
		}

		// see if one of the internal stylesheets should be used
		if( internal_stylesheet ) {
			transform = xsltParseStylesheetMemory( internal_stylesheet, strlen(internal_stylesheet) );
			if( !transform ) {
				fprintf( stderr, "ERROR: internal stylesheet could not be read.\n" );
				goto fail;
			}

			const char *params[3];
			params[0] = "quiet";
			params[1] = "\"false\"";
			params[2] = NULL;
			if( quiet ) {
				params[1] = "\"true\"";
			}
			doc2 = xsltApplyStylesheet( transform, doc, (const char **)&params );

			if( !doc2 ) {
				fprintf( stderr, "ERROR: transformation failed.\n" );
				goto fail;
			}	
			
			xmlFreeDoc( doc );
			doc = doc2;
		}
		
		// treat input as XML, produce SWF
		input.setXML( doc->xmlRootNode, &ctx );
		if( dump ) input.dump();
		out_fp = std_out ? stdout : fopen( outfile, "wb" );
		if( !out_fp ) {
			fprintf(stderr,"ERROR: could not open file '%s' for writing\n", outfile );
			goto fail;
		}
		if( !quiet ) fprintf(stderr,"Writing SWF to %s\n", outfile );
		if( (size = input.save( out_fp, &ctx )) != 0 ) {
			success = true;
			if( !quiet ) fprintf(stderr,"SWF saved to %s (%i bytes).\n", outfile, size );
		}
	}
	
fail:
	if( doc ) xmlFreeDoc( doc );
	if( in_fp && !std_in ) fclose(in_fp);
	if( out_fp && !std_out ) fclose(out_fp);
	
	return success ? 0 : -1;
}

extern "C" {

void R_xml2swf(int *argc, char **argv, int *flag)
{
	swft_register();
	exsltRegisterAll();
	internal_stylesheet = xslt_simple;
	*flag = swfmill_xml2swf(*argc, argv);
}

}
