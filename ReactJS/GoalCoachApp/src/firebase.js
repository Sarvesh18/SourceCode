import * as firebase from 'firebase';

const config = {
};

export const firebaseApp = firebase.initializeApp(config);
export const goalRef=firebase.database().ref('goals');
export const completeRef=firebase.database().ref('complete');
