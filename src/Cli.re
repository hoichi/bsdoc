open Cmdliner;
open Common;

module SharedOpts = {
  let setup_logger = (debug, verbosity) => {
    Logger.verbosity := verbosity;
    let verb_str = verbosity_string(verbosity);
    Logger.debug({j|Set verbosity to $verb_str|j});
    {debug, verbosity};
  };
  let help = [
    `S(Manpage.s_common_options),
    `P("These options are common to all commands."),
    `S("MORE HELP"),
    `P("Use `$(mname) $(i,COMMAND) --help' for help on a single command."),
    `Noblank,
    `S(Manpage.s_bugs),
    `P("Check bug reports at https://github.com/ostera/bsdoc."),
  ];
  let flags = {
    let docs = Manpage.s_common_options;
    let debug = {
      let doc = "Give only debug output.";
      Arg.(value & flag & info(["debug"], ~docs, ~doc));
    };

    let verb = {
      let doc = "Suppress informational output.";
      let quiet = (Quiet, Arg.info(["q", "quiet"], ~docs, ~doc));
      let doc = "Give verbose output.";
      let verbose = (Verbose, Arg.info(["v", "verbose"], ~docs, ~doc));
      Arg.(last & vflag_all([Normal], [quiet, verbose]));
    };

    Term.(const(setup_logger) $ debug $ verb);
  };
};

module SupportFiles = {
  let cmd = {
    let out_dir = {
      let doc = "Output directory of the generated documentation";
      Arg.(
        value
        & opt(file, "./docs")
        & info(["o", "output-dir"], ~docv="DIR", ~doc)
      );
    };

    let doc = {j|Copy the support files (e.g. default theme, JavaScript files)
to the output directory.|j};
    let exits = Term.default_exits;
    let man = [
      `S(Manpage.s_description),
      `P(
        {j|Copies the support files for the generated documentation. This
includes a default stylesheet that can be further customized later on and a small
amount of Javascript to support syntax highlightning.|j},
      ),
      `Blocks(SharedOpts.help),
    ];

    (
      Term.(const(BsDoc.support_files) $ SharedOpts.flags $ out_dir),
      Term.info(
        "support-files",
        ~doc,
        ~sdocs=Manpage.s_common_options,
        ~exits,
        ~man,
      ),
    );
  };
};

module Build = {
  let cmd = {
    let pkg_name = {
      let doc = "The name of your package (e.g., BsDoc)";
      Arg.(
        required
        & pos(~rev=true, 0, some(string), None)
        & info([], ~docv="NAME", ~doc)
      );
    };

    let lib_dir = {
      let doc = "Compilation directory where your .cmt/.cmti files live";
      Arg.(
        value
        & opt(file, "./lib/bs/src")
        & info(["l", "lib-dir"], ~docv="DIR", ~doc)
      );
    };

    let src_dir = {
      let doc = "Source directory where your .mld files live";
      Arg.(
        value
        & opt(file, "./src")
        & info(["s", "source-dir"], ~docv="DIR", ~doc)
      );
    };

    let out_dir = {
      let doc = "Output directory of the generated documentation";
      Arg.(
        value
        & opt(file, "./docs")
        & info(["o", "output-dir"], ~docv="DIR", ~doc)
      );
    };

    let doc = "generate documentation for a BuckleScript project";
    let exits = Term.default_exits;
    let man = [
      `S(Manpage.s_description),
      `P(
        {j|Generates documentation for a BuckleScript project by orchestrating a
global odoc installation.|j},
      ),
      `Blocks(SharedOpts.help),
    ];

    (
      Term.(
        const(BsDoc.build)
        $ SharedOpts.flags
        $ out_dir
        $ pkg_name
        $ src_dir
        $ lib_dir
      ),
      Term.info("build", ~doc, ~sdocs=Manpage.s_common_options, ~exits, ~man),
    );
  };
};

let default_cmd = {
  let doc = "Documentation Generator for BuckleScript projects.";
  let sdocs = Manpage.s_common_options;
  let exits = Term.default_exits;
  let man = SharedOpts.help;
  (
    Term.(ret(const(_ => `Help((`Pager, None))) $ SharedOpts.flags)),
    Term.info("bsdoc", ~version="v0.1.0", ~doc, ~sdocs, ~exits, ~man),
  );
};

let cmds = [Build.cmd, SupportFiles.cmd];

let run = () => {
  %raw
  "process.argv.shift()";
  Term.(exit @@ eval_choice(default_cmd, cmds));
};
