var nbmemcells = 11; // NOMBRE DE CELLULES DE LA MEMOIRE A AFFICHER
var nbiocells = 16;  // NOMBRE DE CELLULES A AFFICHER DES BANDES IN ET OUT
var memshift = 0;    // DECALAGE AFFICHAGE MEMOIRE
var inshift = 0;     // DECALAGE AFFICHAGE BANDE ENTREE
var incell = 0;      // INDEX CASE EN LECTURE DE BANDE D'ENTREE 
var memcell = 0;     // INDEX CASE EN LECTURE DE BANDE D'ENTREE 
var outshift = 0;    // DECALAGE AFFICHAGE BANDE SORTIE
var outcell = 0;     // INDEX CASE EN ECRITURE DE BANDE DE SORTIE
var memcell = 0;     // REGISTRE SELECTION MEMOIRE
var co = 0;          // COMPTEUR ORDINAL
var oldco = 0;	     // VALEUR PRECEDENTE DU CO
var acc = 0;         // ACCUMULATEUR
var cpt = 0;         // COMPTEUR D'INSTRUTIONS DECODEES
var max = 32768;       // VALEUR MAXIMALE DES ENTIERS MANIPULES

var inband = new Array();
var outband = new Array();
var register = new Array();
var program = new Array();
var basis = 'D';
var isprogramload = 0;
var isrunning = 0;
var isend = 0;
var nbrules = 0;


var wordcode = {
  "ADD": 0,
  "SUB": 1,
  "MUL": 2,
  "DIV": 3,
  "MOD": 4,
  "INC": 5,
  "DEC": 6,
  "LOAD": 7,
  "STORE": 8,
  "READ": 9,
  "WRITE": 10,
  "JUMP": 11,
  "JUML": 12,
  "JUMZ": 13,
  "JUMG": 14,
  "STOP": 15,
  "NOP": 16
}



function H2D(h) { return parseInt(h, 16); }

function reduce(n) {
  n = n >> 0;
  reste = n % max;
  if ((reste == 0) && n < 0)
    reste = -max;
  return reste;
}

function info(text) {
}

function start_stop(what) {
  isrunning = what;
  if (what)
    inshift = incell;
}

function exec_rule() {
  operation = { 0: '+', 1: '-', 2: '*', 3: '/', 4: '%', 5: '+', 6: '-' };
  oldco = co;
  rule = program[co];
  if (isend) return 1;
  value = rule.split(":", 3);
  op = value[0];
  var addr = new String(value[1]);
  addrl = addr.length
  if (addr[0] == '0' && addrl > 1)
    addr = parseInt(H2D(addr.substr(1, addrl - 1)));
  else
    addr = parseInt(addr);
  type = value[2];
  code = wordcode[op];
  //		alert("["+co+":"+code+"] "+op+":"+addr+":"+type);
  switch (code) {
    case 0: //ADD
    case 1: //SUB
    case 2: //MUL
    case 3: //DIV
    case 4: //MOD
      if (typeof (register[0]) == 'undefined') {
        register[0] = 0;
      }
      if (type == '#')
        value = addr;
      else {
        if (typeof (register[addr]) == 'undefined')
          register[addr] = 0;
        if (type == '@') {
          ind = register[addr];
          if (typeof (register[ind]) == 'undefined')
            register[ind] = 0;
        }
        else
          ind = addr;
        value = register[ind];
      }
      eval('register[0] = +register[0]' + operation[code] + ' +value');
      register[0] = reduce(register[0]);
      break;
    case 5: // INC
    case 6: // DEC
      ind = addr;
      if (typeof (register[addr]) == 'undefined')
        register[addr] = 0;
      if (type == '@') {
        ind = register[addr];
        if (typeof (register[ind]) == 'undefined')
          register[ind] = 0;
      }
      if (code == 5)
        register[ind] = +register[ind] + 1;
      else
        register[ind] = register[ind] - 1;
      break;
    case 7:  // LOAD
      if (type == '#')
        register[0] = addr;
      else {
        if (typeof (register[addr]) == 'undefined')
          register[addr] = 0;
        if (type == '@') {
          ind = register[addr];
          if (typeof (register[ind]) == 'undefined')
            register[ind] = 0;
        }
        else
          ind = addr;
        register[0] = register[ind];
      }
      break;
    case 8:  // STOR
      if (typeof (register[0]) == 'undefined') {
        alert("Accumulateur non défini !");
        register[0] = 0;
      }
      if (type == '@') {
        ind = register[addr];
        if (typeof (register[addr]) == 'undefined')
          register[addr] = 0;
      }
      else
        ind = addr;
      register[ind] = register[0];
      break;
    case 9:  // READ
      register[0] = inband[incell++];
      break;
    case 10:  // WRIT
      outband[outcell++] = register[0];
      break;
    case 11: // JUMP
      if (type == '@') {
        ind = register[addr];
        addr = ind;
      }
      else
        ind = addr;
      if (addr < nbrules)
        co = addr;
      else
        info("SAUT IMPOSSIBLE");
      break;
    case 12: // JUML
      if (typeof (register[0]) == 'undefined') {
        register[0] = 0;
        co++;
      }
      else {
        if (type == '@') {
          ind = register[addr];
          addr = ind;
        }
        else
          ind = addr;
        if (register[0] < 0) {
          if (addr < nbrules)
            co = addr;
          else
            info("SAUT IMPOSSIBLE");
        }
        else
          co++;
      }
      break;
    case 13: // JUMZ
      if (typeof (register[0]) == 'undefined')
        register[0] = 0;
      if (register[0] == 0) {
        if (type == '@') {
          ind = register[addr];
          addr = ind;
        }
        else
          ind = addr;
        if (addr < nbrules)
          co = addr;
        else
          info("SAUT IMPOSSIBLE");
      }
      else
        co++;
      break;
    case 14: // JUMG
      if (typeof (register[0]) == 'undefined') {
        register[0] = 0;
        co++;
      }
      else {
        if (type == '@') {
          ind = register[addr];
          addr = ind;
        }
        else
          ind = addr;
        if (register[0] > 0) {
          if (addr < nbrules)
            co = addr;
          else
            info("SAUT IMPOSSIBLE");
        }
        else
          co++;
      }
      break;
    case 15: // STOP
      info("FIN DE L'&Eacute;XECUTION");
      start_stop(0);
      isend = 1;
      break;
    case 16: // NOP
      co++;
      break;
  }
  cpt++;
  if (code < 11) co++;
  if (co < nbrules) {
    memcell = find_sm();
    show_in();
    show_out();
    memshift = memcell;
    if (memcell > 0)
      memshift = memcell - 1;
    // FLAG
    show_memory();
    show_rule();
  }
  else {
    show_memory();
    show_cpt();
    isend = 1;
  }
}

function find_sm() {
  rule = program[co];
  triple = rule.split(":", 3);
  op = triple[0];
  var addr = new String(triple[1]);
  addrl = addr.length
  if (addr[0] == '0' && addrl > 1)
    addr = parseInt(H2D(addr.substr(1, addrl - 1)));
  else
    addr = parseInt(addr);
  type = triple[2];
  code = wordcode[op];
  switch (type) {
    case '#':
      memcell = 0;
      break;
    case '@':
      memcell = register[addr];
      break;
    default:
      if (code < 9)
        memcell = addr;
      else
        memcell = 0;
  }
  return memcell;
}

/*------------------------------------------------------------------------
  Affiche le contenu du compteur d'instruction
  -------------------------------------------------------------------------*/
function show_cpt() {
}


/*------------------------------------------------------------------------
  Affiche les instructions (inst courante + scroll automatique). Met à jour
  l'affichage du compteur ordinal et du registre de selection mem
  -------------------------------------------------------------------------*/
function show_rule() {
}

/*------------------------------------------------------------------------
  Affiche le contenu des registres mémoire (scroll automatique)
  et de l'accumulateur R[0]
  -------------------------------------------------------------------------*/
function show_memory() {
}

function show_in() {
}

function show_out() {
}

var file = process.argv[2];
var inputfile = process.argv[3];

const fs = require('node:fs');

function loadprogram() {
  fs.readFile(file, 'utf8', (err, data) => {
    if (err) {
      console.error(err);
      return;
    }
    data.split('\n').forEach((line, index) => {
      if (line == '') {
        return;
      }
      var rule = line.split(';')[0].trim().split(' ');
      var instr = rule[0];
      var addr = '';
      var type = '';
      if (rule.length > 1) {
        addr = rule[1];
        if (addr[0] == '#' || addr[0] == '@') {
          type = addr[0];
          addr = addr.substr(1);
        }
      }
      if (addr == '') {
        program.push(instr);
      } else {
        program.push(instr + ':' + addr + ':' + type);
      }
    });
    nbrules = program.length
    console.log(program);
    loadinput();
  });
}


function loadinput() {
  fs.readFile(inputfile, 'utf8', (err, data) => {
    if (err) {
      console.error(err);
      return;
    }
    data.split('\n').forEach((line, index) => {
      if (line == '') {
        return;
      }
      inband.push(parseInt(line));
    });
    console.log(inband);
    mainloop();
  });
}

function mainloop() {
  while (!isend) {
    exec_rule();
  }

  console.log(outband);
}

loadprogram();



