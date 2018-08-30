import * as firebase from 'firebase';

const config = {
};

export const firebaseApp = firebase.initializeApp(config);

//export const storageRef = firebase.storage().ref('images');
//export const databaseRef = firebase.database().ref('Database');
