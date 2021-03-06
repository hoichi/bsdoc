// Generated by BUCKLESCRIPT VERSION 4.0.11, PLEASE EDIT WITH CARE
'use strict';

var OS = require("./OS.bs.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Logger = require("./Logger.bs.js");
var Filename = require("bs-platform/lib/js/filename.js");

function odoc(param) {
  return OS.run("odoc", param);
}

function support_files(out_dir) {
  OS.run("odoc", /* :: */[
        "support-files",
        /* :: */[
          "--output-dir",
          /* :: */[
            out_dir,
            /* [] */0
          ]
        ]
      ]);
  return /* () */0;
}

function compile(lib_dir, pkg_name, file_name) {
  var param_001 = /* :: */[
    "-I",
    /* :: */[
      lib_dir,
      /* :: */[
        "--pkg=" + (String(pkg_name) + ""),
        /* :: */[
          file_name,
          /* [] */0
        ]
      ]
    ]
  ];
  var param = /* :: */[
    "compile",
    param_001
  ];
  OS.run("odoc", param);
  return /* () */0;
}

function compile_mld(lib_dir, out_file, pkg_name, file_name) {
  var param_001 = /* :: */[
    "-I",
    /* :: */[
      lib_dir,
      /* :: */[
        "--pkg=" + (String(pkg_name) + ""),
        /* :: */[
          "-o",
          /* :: */[
            out_file,
            /* :: */[
              file_name,
              /* [] */0
            ]
          ]
        ]
      ]
    ]
  ];
  var param = /* :: */[
    "compile",
    param_001
  ];
  OS.run("odoc", param);
  return /* () */0;
}

function html(lib_dir, out_dir, file_name) {
  OS.run("odoc", /* :: */[
        "html",
        /* :: */[
          "-I",
          /* :: */[
            lib_dir,
            /* :: */[
              "-o",
              /* :: */[
                out_dir,
                /* :: */[
                  "--syntax=re",
                  /* :: */[
                    "--semantic-uris",
                    /* :: */[
                      file_name,
                      /* [] */0
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]);
  return /* () */0;
}

var Bin = /* module */[
  /* odoc */odoc,
  /* support_files */support_files,
  /* compile */compile,
  /* compile_mld */compile_mld,
  /* html */html
];

function filename(path) {
  return Filename.chop_extension(Curry._1(Filename.basename, path));
}

function as_odoc(name) {
  return Filename.chop_extension(Curry._1(Filename.basename, name)) + ".odoc";
}

function cmti_to_odoc(lib_dir, pkg_name, cmti) {
  var odoc = Filename.chop_extension(Curry._1(Filename.basename, cmti)) + ".odoc";
  Logger.debug("Compiling " + (String(cmti) + (" to " + (String(odoc) + "..."))));
  compile(lib_dir, pkg_name, Filename.concat(lib_dir, cmti));
  return odoc;
}

function mld_to_odoc(lib_dir, src_dir, pkg_name, mld) {
  var odoc = "page-" + (Filename.chop_extension(Curry._1(Filename.basename, mld)) + ".odoc");
  Logger.debug("Compiling " + (String(mld) + (" to " + (String(odoc) + "..."))));
  compile_mld(lib_dir, Filename.concat(lib_dir, odoc), pkg_name, Filename.concat(src_dir, mld));
  return odoc;
}

function odoc_to_html(lib_dir, out_dir, odoc) {
  var html$1 = Filename.chop_extension(Curry._1(Filename.basename, odoc)) + ".html";
  Logger.debug("Compiling " + (String(odoc) + (" to " + (String(html$1) + "..."))));
  html(lib_dir, out_dir, Filename.concat(lib_dir, odoc));
  return html$1;
}

exports.Bin = Bin;
exports.support_files = support_files;
exports.filename = filename;
exports.as_odoc = as_odoc;
exports.cmti_to_odoc = cmti_to_odoc;
exports.mld_to_odoc = mld_to_odoc;
exports.odoc_to_html = odoc_to_html;
/* OS Not a pure module */
