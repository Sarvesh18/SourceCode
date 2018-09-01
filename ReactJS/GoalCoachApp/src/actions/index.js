import {SIGNED_IN} from '../constants';
import {SET_GOALS} from '../constants';

console.log('actions');
export function logUser(email) {
  const action = {
    type: SIGNED_IN,
    email: email
  }
  console.log('actions logUser action',action);
  return action;
}

export function setGoals(goals) {
  const action = {
    type: SET_GOALS,
    goals: goals
  }
  console.log('actions setGoals action',action);
  return action;
}
