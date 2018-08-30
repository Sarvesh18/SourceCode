import {ADD,SUB,DIV,MUL,CONCAT,EQUAL} from '../constants';

export function concat(ch) {
  const action= {
    type:CONCAT,
    ch
  }
  console.log('CONCAT action',action);
  return action;
}

export function add(ch) {
  const action= {
    type:ADD,
    ch
  }
  console.log('ADD action',action.ch);
  return action;
}

export function sub(ch) {
  const action= {
    type:SUB,
    ch
  }
  console.log('SUB action',action.ch);
  return action;
}

export function mul(ch) {
  const action= {
    type:MUL,
    ch
  }
  console.log('MUL action',action.ch);
  return action;
}

export function div(ch) {
  const action= {
    type:DIV,
    ch
  }
  console.log('DIV action',action.ch);
  return action;
}

export function equal() {
  const action= {
    type:EQUAL
  }
  console.log('EQUAL action',action);
  return action;
}
