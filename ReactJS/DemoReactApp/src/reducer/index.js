import {combineReducers} from 'redux';
import test from './test.js';
import thunkTest from './thunkTest.js';

const reducers = combineReducers({
    test,
    thunkTest
}) 

export default reducers;