import {TEST} from '../constant';
 
const test = (state=['gggggggg'], action) => { 
    console.log('TEST');
    switch(action.type) {
        case TEST: 
            console.log('case');
            return [...state, {text:action.text}];
        default: 
            console.log('default',state);
            return state;
    }
}
export default test;