var editor = ace.edit("editor");

setupEditor();
function setupEditor() {
    var langTools = ace.require("ace/ext/language_tools");

    editor.setTheme("ace/theme/dracula");
    editor.getSession().setMode("ace/mode/general_assembly");
    editor.setOptions({
        enableBasicAutocompletion: true,
        enableLiveAutocompletion: true,
        enableSnippets: true
    })

    var instruction_completer =
    {
        getCompletions: (editor, session, pos, prefix, callback) => {callback(null,cpu_description.instructions);}
    };

    langTools.addCompleter(instruction_completer);
}