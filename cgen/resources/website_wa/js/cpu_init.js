json = Module.cwrap('json', 'string');
simulate = Module.cwrap('simulate');
reset = Module.cwrap('reset');
assemble = Module.cwrap('assemble',null, 'string');

function cpu_json()
{
  return JSON.parse(json());
}

function cpu_simulate()
{
  simulate();
}

function cpu_reset()
{
  reset();
}

function cpu_flash(code)
{
  var ptr  = allocateUTF8(code);
  assemble(ptr);
  _free(ptr);
}
