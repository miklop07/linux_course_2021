pkgdata_DATA=ru/LC_MESSAGES/find.mo

ru.po: ../src/find.c
	xgettext --msgid-bugs-address=miklop07@gmail.com --keyword=_ --add-comments ../src/find.c -o find.pot
	msgmerge -U $@ find.pot

ru/LC_MESSAGES/find.mo: ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt -o $@ $<
