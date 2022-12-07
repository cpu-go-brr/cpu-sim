var cpu_server_url = "http://localhost:8080";

function cpu_json() {
    return JSON.parse($.ajax({type: "GET", url: cpu_server_url + "/get", async:false}).responseText);
}

function cpu_flash(code) {
    $.post(cpu_server_url + "/flash", code);
}


function cpu_simulate() {
    $.get(cpu_server_url + "/simulate");
}