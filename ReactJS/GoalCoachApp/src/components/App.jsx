import React, { Component } from 'react';
import logo from '../logo.svg';
import './App.css';
import {firebaseApp} from '../firebase';
import {connect} from 'react-redux';
import AddGoal from './AddGoal';
import GoalList from './GoalList';
import CompleteGoalList from './CompleteGoalList';

console.log('App');
class App extends Component {
  signOut() {
    console.log('signout');
    firebaseApp.auth().signOut();
  }
  render() {
    return (
      <div className="App">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h1 className="App-title">Welcome to React</h1>
        </header>
        <p className="App-intro">
          To get started, edit <code>src/App.js</code> and save to reload.
        </p>
        <hr/>
        <h3>Add Goal</h3>
        <AddGoal />
        <hr/>
        <h3>Goal List</h3>
        <GoalList />
        <hr/>
        <h3>Complete Goal List</h3>
        <CompleteGoalList />
        <hr/>
        <button type="button" className="btn btn-danger" onClick={
          ()=>this.signOut()
        }>SignOut</button>
      </div>
    );
  }
}

function mapStateToProps(state) {
  console.log('App mapStateToProps state',state);
  return {}
}
/*
function mapDispatchToProps(dspatch) {
  return bindActionCreators({actions},dispatch);
}
*/
export default connect(mapStateToProps,null)(App);
