import {SIGNED_IN} from '../constants';

console.log('reducer_user');
let user= {
  email: null
}
export default (state=user,action) => {
  console.log('reducer_user export');
  switch (action.type) {
    case SIGNED_IN:
        const {email} =action;
        user={email: email};
        console.log('reducer_user signin user',user);
        return user;
    default:
      console.log('reducer_user default state',state);
      return state;

  }
}
