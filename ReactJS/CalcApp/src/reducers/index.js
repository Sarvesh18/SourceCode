import {ADD,SUB,MUL,DIV,CONCAT,EQUAL} from '../constants';

let value=['','',9,8,7,'+',6,5,4,'-',3,2,1,'*','.',0,'#','/'];

export default (state=value,action) => {
  console.log('reducers');
  switch(action.type) {
    case CONCAT:
      console.log('CONCAT reducer');
      value[0]=state[0]+action.ch;
      return [...value];
    case ADD:
      console.log('ADD reducer');
      value[0]=state[0]+action.ch;
      return [...value];
    case SUB:
      console.log('SUB reducer');
      value[0]=state[0]+action.ch;
      return [...value];
    case MUL:
      console.log('MUL reducer');
      value[0]=state[0]+action.ch;
      return [...value];
    case DIV:
      console.log('DIV reducer');
      value[0]=state[0]+action.ch;
      return [...value];
    case EQUAL:
      console.log('EQUAL reducer');
      return [...value];
    default:
      console.log('default reducer',state,' ',action);
      return state;
  }
}
