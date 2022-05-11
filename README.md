GeSHi Filter
======================

The GeShi Filter is a Backdrop CMS module for syntax highlighting pieces of
source code. It implements a filter that formats and highlights the syntax of
source code between for example <code>...</code>.

<!-- All lines in this file should be no more than 80 characters long for
legibility, unless including a URL or example that requires the line not wrap.
(The above line starting with "Foo" is 79 characters for reference.)
Detail in READMEs should be limited to the minimum required for installation and
getting started. More detailed documentation should be moved to a GitHub wiki
page, for example, https://github.com/backdrop-contrib/setup/wiki/Documentation. -->

Requirements
------------

This module requires the third-party library GeShi 1.0.x (Generic Syntax
Highlighter, written by Nigel McNie) which can be found at
  http://qbnz.com/highlighter
See installation procedure below for more information.

This module requires that the following modules are also enabled:

  * [Libraries API](https://backdropcms.org/project/libraries)


Installation
------------

GeSHi Filter

- Install this module using the official Backdrop CMS instructions at
  https://docs.backdropcms.org/documentation/extend-with-modules.

- Visit the configuration page under Administration > Configuration >
  Content authoring > Text editors and formats or
  [GeSHi Filter](admin/config/content/formats/geshifilter) and enter the
  required information.

- Download the GeSHi library from
  https://sourceforge.net/projects/geshi/files/geshi/
  Make sure you download a version of the branch 1.0.x and not a version
  from the branch 1.1.x (also described as geshi-dev), which is not yet
  supported by the GeSHi filter module.
  Place the entire extracted 'geshi' folder (which contains geshi.php)
  in a libraries directory (typically /libraries/geshi).

GeSHi Fields

- Install this module using the official Backdrop CMS instructions at
  https://docs.backdropcms.org/documentation/extend-with-modules.

USAGE
-----

```
The basic usage (with the default settings) is:
  <code language="java">
  for (int i; i<10; ++i) {
    dothisdothat(i);
  }
  </code>
When language tags are enabled (like "<java>" for Java) you can also do
  <java>
  for (int i; i<10; ++i) {
    dothisdothat(i);
  }
  </java>
```

More options and tricks can be found in the filter tips of the text format at
www.example.com/?q=filter/tips .

Issues <!-- This section is required. -->
------

Bugs and feature requests should be reported in [the Issue Queue](https://github.com/backdrop-contrib/geshifilter/issues).

Current Maintainers <!-- This section is required. -->
-------------------

- [Justin Christoffersen](https://github.com/larsdesigns).
- [Jen Lampton](https://github.com/jenlampton).

<!-- You may also wish to add: -->
- Seeking additional maintainers.

Credits <!-- This section is required. -->
-------

- Ported to Backdrop CMS by [Justin Christoffersen](https://github.com/larsdesigns)
- Ported to Backdrop CMS by [Nate Lampton](https://github.com/quicksketch)
- Port to Backdrop CMS sponsored by [Exceljet](https://exceljet.net)

- Originally written for Drupal by Vincent Filby.
- Port to Drupal 4.7:
  - Vincent Filby
  - Michael Hutchinson
  - Damien Pitard

- Port to Drupal 5:
  - rötzi (http://drupal.org/user/73064)
  - Stefaan Lippens (http://drupal.org/user/41478)

License <!-- This section is required. -->
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.

<!-- If your project includes other libraries that are licensed in a way that is
compatible with GPL v2, you can list that here too, for example: `Foo library is
licensed under the MIT license.` -->
