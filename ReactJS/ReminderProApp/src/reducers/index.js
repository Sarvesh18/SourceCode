import {ADD_REMAINDER,DEL_REMAINDER} from '../constants';
import {bake_cookie,read_cookie} from 'sfcookies';

const add = (action) => {
  console.log('reducers add action',action);
  let { text, dueDate} = action;
  //const {remainders} =this.props;
  //const remainders =this.props.remainders;
  return  {
    //text: action.text
    id: Math.random(),
    text: text,
    dueDate: dueDate
  }
}

const remove = (state=[], id) => {
  const a= state.filter(add => add.id !== id);
  console.log('reducers remove remainders', a);
  return a;
}

const reducer =(state=[], action)=> {
  console.log('reducer');
  let remainders=null;
  state=read_cookie('remainders');
  switch(action.type) {
    case ADD_REMAINDER :
      remainders=[...state, add(action)];
      bake_cookie('remainders',remainders);
      console.log('reducers ADD_REMAINDER x',remainders);
      return remainders;
    case DEL_REMAINDER :
      remainders=remove(state,action.id);
      bake_cookie('remainders',remainders);
      console.log('reducers DEL_REMAINDER x',remainders);
      return remainders;
    default:
    console.log('reducers default state',state);
    return state;
  }
}

export default reducer;
