var cpu_description;
var internal_cpu_content = document.getElementById("internal_memory_content");
var external_memory_content = document.getElementById("external_memory_content");

if(typeof Module != 'undefined')
{
    Module.onRuntimeInitialized = () => {
        $.getJSON("cpu.json", function (data) {
            cpu_description = data;
            loadCPU();
        });}
}
else
{
    $.getJSON("cpu.json", function (data) {
        cpu_description = data;
        loadCPU();
    });
}

function loadCPU() 
{
    var result = cpu_json()
    displayCPU(transformInternalMemory(result.internal));
    setupMemorySelect(result.external);
}
function getValueHex(val, bits) {
    return ("0000" + val.toString(16)).substr(-bits);
}
function displayMemory(data, name) {
    external_memory_content.innerHTML = "";
    var lines = data[name].vals.length / 16;
    var line_places_needed = Math.max(1, Math.ceil(Math.log2(lines) / 4));
    var word_places_needed = Math.ceil(data[name].bits / 4);

    var s = "<table><tr><td></td>";
    for (var x = 0; x < 16; x++)
        s += "<td> " + x.toString(16) + "</td>";

    s += "</tr>";

    for (var y = 0; y < lines; y++) {
        s += "<tr>";
        s += "<td> " + getValueHex(y, line_places_needed) + "</td>";
        for (var x = 0; x < 16; x++)
            s += "<td> " + getValueHex(data[name].vals[x + 16 * y], word_places_needed) + "</td>";

        s += "</tr>";
    }
    s += "</table>";
    external_memory_content.innerHTML = s;

}
var init_memory = false;
var memorySelect = document.getElementById("memory_select");
function setupMemorySelect(data) {
    if (!init_memory) {
        init_memory = true;

        Object.keys(data).forEach(function (key) {
            memorySelect.innerHTML += '<option value="' + key + '">' + key + '</option>';
        });

        memorySelect.onchange = () => displayMemory(data, memorySelect.value);
    }
    displayMemory(data, memorySelect.value);
}


function calculateVal(data) {
    var bits = 0;
    var val = 0;

    const keys = Object.keys(data);
    for (let i = keys.length - 1; i >= 0; i--) {
        let key = keys[i];
        if (data[key].val == null) {
            var child = calculateVal(data[key]);

            bits += child.size;
            val = (val << child.size) + child.val;

        }
        else {
            bits += data[key].bits;
            val = (val << data[key].bits) + data[key].val;

        }
    }

    return { "bits": bits, "val": val };
}

function addInternalMemory(data, val, col, row) {
    internal_cpu_content.innerHTML +=
        '<div class="internal_memory_element" style="grid-row: ' + row + '; grid-column: ' + col + ' / span ' + val.size + '">\
                        <span>'+ getValueHex(data.val, Math.ceil(data.bits / 4)) + '</span>\
                    </div>';
}

function addText(name, col, row) 
{
    internal_cpu_content.innerHTML +=
        '<div class="internal_memory_element" style="grid-row: ' + row + '; grid-column: ' + col + ' / span ' + name.length + '">\
        <span>'+ name + '</span></div>';
}

function transformInternalMemory(data) {
    internal_memory_map = {};
    Object.keys(data).forEach(function (key) {
        if (data[key].val == null) {
            internal_memory_map = Object.assign(internal_memory_map, transformInternalMemory(data[key]));
            internal_memory_map[key] = calculateVal(data[key]);

        }
        else {
            internal_memory_map[key] = data[key];
        }

    })

    return internal_memory_map;
}

function displayCPU(map) 
{
    internal_cpu_content.innerHTML = "";
    var index_Y = 1;
    for (var row in cpu_description.internal) {
        var index_X = 1;
        for (var cell in cpu_description.internal[row]) {

            var val = cpu_description.internal[row][cell];
            
            if (typeof (val) === "number") {
                index_X += val;
                continue;
            }
            else if(typeof (val) === "string") 
            {
                addText(val, index_X,index_Y);
                index_X += val.length;
                continue;
            }
            else
            {
                addInternalMemory(map[val.name], val, index_X, index_Y);
                index_X += val.size;
            }
        }
        index_Y += 1;
    }
}
