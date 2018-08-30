import user from './reducer_user';
import goals from './reducer_goals';
import {combineReducers} from 'redux';

export default combineReducers ({
  user,
  goals
})
