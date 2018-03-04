DIR=`/bin/pwd | sed -e "s/\/auto\/u\/cma//"`
all atg:
	@rm -f atg
	@chmod -R u+rw,go+r,go-w .
	@(echo "#!/bin/sh "; \
	  echo "DIR=$(DIR)"; \
	  echo "PATH=\$$DIR:\$$PATH \\"; \
	  echo "XENVIRONMENT=\$$DIR/Atg \\"; \
	  echo "XKEYSYMDB=\$$DIR/XKeysymDB \\"; \
	  echo "ATG_HELP_DIR=\$$DIR/help \\"; \
	  echo "\$$DIR/atgbinary \$$*") >> atg
	@chmod a+rx atg


