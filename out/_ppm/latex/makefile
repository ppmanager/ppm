
-include _project

COMP = texify
CFLAGS = --pdf --run-viewer


build: 
	@$(COMP) $(CFLAGS) $(FILE_NAME).tex
	@rm -f $(FILE_NAME).aux
	@rm -f $(FILE_NAME).lof
	@rm -f $(FILE_NAME).log
	@rm -f $(FILE_NAME).toc

clean:
	@rm -f $(FILE_NAME).aux
	@rm -f $(FILE_NAME).lof
	@rm -f $(FILE_NAME).log
	@rm -f $(FILE_NAME).pdf
	@rm -f $(FILE_NAME).toc
	
