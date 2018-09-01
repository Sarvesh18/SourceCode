import {ADD_REMAINDER,DEL_REMAINDER} from '../constants';

export const addRemainder = (text,dueDate) => {
  const action = {
    type: ADD_REMAINDER,
    text: text,
    dueDate: dueDate
  }
  console.log('actions addRemainder action',action);
  return action;
}

export const delRemainder = (id) => {
  const action = {
    type: DEL_REMAINDER,
    id: id
  }
  console.log('actions delRemainder action',action);
  return action;
}
