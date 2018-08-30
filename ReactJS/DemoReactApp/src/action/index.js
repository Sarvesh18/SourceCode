import {TEST, THUNK} from '../constant';

export const testAction = (text) => {
    const action = {
        type: TEST,
        text
    }
    console.log('testAction');
    return action;
}

export const thunkAction = (text) => {
    console.log('thunkAction');
    return (dispatch,getState) => {

/*
    return func().then(
      sauce => dispatch(makeASandwich(forPerson, sauce)),
      error => dispatch(apologize('The Sandwich Shop', forPerson, error))
    );
*/


        console.log('getState()',getState());
        dispatch(testAction(text));
        setTimeout(() => {
            // Yay! Can invoke sync or async actions with `dispatch`
            dispatch(thunkAction(text));
          }, 1000);
    }
}