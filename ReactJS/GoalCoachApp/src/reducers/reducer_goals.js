import {SET_GOALS} from '../constants';

console.log('reducer_goals');
export default (state=[],action)=> {
  console.log('reducer_goals export');
  switch(action.type) {
    case SET_GOALS:
      const {goals}  = action;
        console.log('reducer_goals GET_GOALS goals',goals);
      return goals;
    default:
      console.log('reducer_goals default state',state);
      return state;
  }
}
