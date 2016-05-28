Synopsis
-------------
This project represents the Translator for the model programming language.
Translation based on the l-graph.

Model programming language description
--------------------

Model language supports:
* while do
* if then else
* read
* write
* +,-,/,*
* :=

The code examples you can see at the test directory lgraphtranslator/translatorCPP/test/testdata


How to build
------------------------
To build the .so from the list of the files you should run make file.


How to use
-----------------------
To use the shared library you should add the header Interpretator.h to your file and show ld where to find shared library.
For example 

	int main(int count,char ** args)
	{
		Interpretator inter("pathtofilewithCode.modelLang");
		inter.interpretation();
		return 0;
	}
buid it using rpath:
* g++ -Lpathtolibrary -Wl,-rpath=$pathtolibrary -o testProgram testProgram.cpp -ltranslator






