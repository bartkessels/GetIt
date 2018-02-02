# Translate

This is a small tutorial on adding / updating languages.

## Requirements

Before continuing please make sure you've got `xgettext` installed on
your system.

## Add new language

When you add a new language you need to add a few more flags to the
`xgettext` command to setup all the required settings.

```
$ cd po
$ xgettext -f POTFILES.in -o <language_code>.po \
    --copyright-holder="<your_full_name>" \
    --package-name=getit \
    --package-version=<latest_release_of_getit> \
    --msgid-bugs-address="<your_email_address>"
```

When you open your created `<language_code>.po` file you will see that the file
start with this information, please enter the correct data.

```
# SOME DESCRIPTIVE TITLE.
# Copyright (C) YEAR <your_full_name>
# This file is distributed under the same license as the getit package.
# FIRST AUTHOR <EMAIL@ADDRESS>, YEAR.
#
#, fuzzy
msgid ""
msgstr ""
"Project-Id-Version: getit 4.0.6\n"
"Report-Msgid-Bugs-To: <your_email_address>\n"
"POT-Creation-Date: 2018-02-02 23:19+0100\n"
"PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE\n"
"Last-Translator: FULL NAME <EMAIL@ADDRESS>\n"
"Language-Team: LANGUAGE <LL@li.org>\n"
"Language: \n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=UTF-8\n"
"Content-Transfer-Encoding: 8bit\n"
```

You only need to update these lines

- `SOME DESCRIPTIVE TITLE.`
- `Copyright (C) YEAR <your_full_name>`
- `FIRST AUTHOR <EMAIL@ADDRESS>, YEAR`
- `Last-Translator: FULL NAME <EMAIL@ADDRESS>`
- `Language: `

and remove the `#, fuzzy` line completely.

Change this to I.E.:

- `Dutch translation for GetIt`
- `Copyright (C) 2018 Bart Kessels`
- `Bart Kessels <bartkessels@bk-mail.com>, 2018`
- `Last-Translator: Bart Kessels <bartkessels@bk-mail.com>`
- `Language: nl`

---

Once you have added the translations please update `data/net.bartkessels.getit.appdata.xml.in`
and add the new language in the `<languages>` tag.

## Update language

```
$ cd po
$ xgettext -f POTFILES.in -j -o <language_code>.po \
    --omit-header
```

The `-f POTFILES.in` flag will read all the files specified in
the `POTFILES.in` file.

The `-j` flag will make sure the contents of the file won't be overwritten

The `-o <language_code>.po` flag specifies the file to which the new translations
will be added

---

After the `<language_code>.po` file has been updated please open the file with
a text editor and add your name to the list of other authors,
make sure the newest author is above the older authors, like this:

```
# This file is distributed under the same license as the GetIt package.
# Bart Kessels <bartkessels@bk-mail.com>, 2017.
# Chris Castelio <cc@domain.com>, 2016.
```

And edit this line to your own full name and email address:

- `Last-Translator: FULL NAME <EMAIL@ADDRESS>`

## Check .po file

Wheter you've created a new `.po` file or updated a `.po` file always make sure
the file doesn't contain any errors by using the `msgfmt` tool.

```
$ msgfmt -C <language_code>.po
```

It this command executes without any output the file doesn't contain any errors
