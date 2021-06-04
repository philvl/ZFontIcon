### Release v2.0.10 - 2021-06-04
- Add UCS-4/UTF-32 unicode glyph support (4 bytes unicode character)
- Update helper for Font Awesome 6.0.0-beta1 (requires a FA pro licence to get alpha fonts)
- Update helper for Google Material Design Icons 4 (github master ab12f16 - 2021-05-11)

### Release v2.0.9 - 2021-04-01
- Update helper for Font Awesome 6.0.0-alpha3 (requires a FA pro licence to get alpha fonts)
- Update helper for Font Awesome 5.15.3

### Release v2.0.8 - 2021-01-08
- Update helper for Font Awesome 5.15.2

### Release v2.0.7 - 2020-12-25
- Update helper for Font Awesome 6.0.0-alpha2 (requires a FA pro licence to get alpha fonts)

### Release v2.0.6 - 2020-12-11
- BugFix: Qt 6.0.0 compatibility
  - Use QFontDatabase static functions
  - Resolve ambiguous glyph type: use ushort instead of QChar

### Release v2.0.5 - 2020-11-15
- Sample:
  - CheatSheet: add icon search engine
  - CheatSheet: show unicode value in tooltip
  - BugFix: executable recognizes as shared library under Ubuntu Linux likes

### Release v2.0.4 - 2020-11-09
- ZFontIcon
  - Add function isRegistered();
- Fonts
  - Bugfix: Google material icons not run on Windows
- Helpers:
  - Add helper for Font Awesome 6.0.0-alpha1 (requires a FA pro licence to get alpha fonts)
  - Add meta-object support for fonts helpers namespaces (you can now iterate over namespaces)
- Sample:
  - Add prewiew tabs for FA6
  - Add a font cheatsheet tool
- Add CHANGELOG.md file

### Release v2.0.3 - 2020-11-08
- FontAwesome 5.x: Update from v5.13.0 to v5.15.1
- FontAwesome 4.7.0: Add glyph aliases
- Google Material Icons: 
  - Add support for v4.x
  - Remove support for v2.2
- Update sample

### Release v2.0.2 - 2020-07-06
- Minor bugfix: Use the default color when color is not set

### Release v2.0.1 - 2020-06-19
- Adding a scale factor argument to static icon() functions
- Minor changes

### Release v2.0.0 - 2020-06-18
- Add font style customization according to icon state
- Add glyph customization according to icon state
- Add color customization according to icon mode and state
- Add scale factor customization according to icon state
- Update example/sample

### Release v1.0.1 - 2020-06-06
- Change "ZFontIcon::icon" function call (Prepare future release)

### Release v1.0.0 - 2020-06-04
- Reconcile Windows, Linux and Mac by adding a font matching algorithm
- Improve addFont function
- Improve example/sample
