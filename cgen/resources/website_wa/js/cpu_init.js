json = Module.cwrap('json', 'string');
simulate = Module.cwrap('simulate');
reset = Module.cwrap('reset');

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

function cpu_flash()
{
  reset();
}
