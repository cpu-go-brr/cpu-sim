json = Module.cwrap('json', 'string');
simulate = Module.cwrap('simulate');
clear = Module.cwrap('clear');

function cpu_json()
{
  return JSON.parse(json());
}

function cpu_simulate()
{
  simulate();
}

function cpu_clear()
{
  clear();
}
