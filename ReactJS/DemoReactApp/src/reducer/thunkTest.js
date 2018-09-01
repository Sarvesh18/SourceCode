import {THUNK} from '../constant';

const thunkTest = (state=['pppppp'], action) => { 
    console.log('THUNK');
    switch(action.type) {
        case THUNK: 
            console.log('caseT');
            return null;
        default: 
            console.log('deafultT',state);
            return state;
    }
}

export default thunkTest; 