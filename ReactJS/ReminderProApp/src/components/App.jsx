import React, { Component } from 'react';
import logo from '../logo.svg';
import './App.css';

import {connect} from 'react-redux';
import {bindActionCreators} from 'redux';
import {addRemainder, delRemainder} from '../actions';

import moment from 'moment';


class App extends Component {
  constructor(props) {
    super(props);
    this.state={
      text: '',
      dueDate: ''
    }
  }

  additionRemainder() {
    console.log('additionRemainder');
    this.props.addRemainder(this.state.text,this.state.dueDate);
  }
  deleteRemainder(id) {
    console.log('deleteRemainder');
    this.props.delRemainder(id);
  }
  renderRemainder() {
    //const {remainders} =this.props;
    const remainders =this.props.remainders;
    console.log('renderRemainder props',this.props);
    console.log('renderRemainder remainders',remainders);
    return(
      <ul className="list-group">{
        remainders.map(i=> {
            return (
              <li key={i.id} className="list-group-item">
                <div>
                  <div>{i.text}</div>
                  <div>{moment(new Date(i.dueDate)).fromNow()}</div>
                  <div onClick={()=>this.deleteRemainder(i.id)}>&#x2715;</div>
                </div>
              </li>
            )
        })
      }
    </ul>
  )
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


        <form className="form-inlined">
          <input type="text" placeholder="Enter Remainder"
            onChange={
              event => {
                console.log('event', event.target.value);
                this.setState({text:event.target.value});
              }
            }
          />
          <input type="datetime-local"
            onChange={
              event => {
                console.log('event', event.target.value);
                this.setState({dueDate:event.target.value});
              }
            }
          />
          <button type="button" className="btn btn-success"
            onClick={()=> this.additionRemainder()}>Add</button>
        </form>
        {this.renderRemainder()}
      </div>
    );
  }
}

function mapDispatchToProps(dispatch) {
  console.log('mapDispatchToProps');
  return bindActionCreators({addRemainder,delRemainder},dispatch);
}
function mapStateToProps(state) {
  console.log('mapStateToProps state',state);
  return {
    remainders: state
  }
}
export default connect(mapStateToProps,mapDispatchToProps)(App);
