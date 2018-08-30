import React, { Component } from 'react';
import logo from '../static/logo.svg';
import style from '../style/style.css';

import Home from './Home.jsx';
import Sign from './Sign.jsx';
import Signin from './Signin.jsx';
import Signout from './Signout.jsx';
import Signup from './Signup.jsx';

import { BrowserRouter, Switch, Route, Link, Redirect } from "react-router-dom";

class App extends Component {
  constructor(props) {
    super(props);

    console.log('App props',props);
    
    const auth=props.auth;
    this.state = {
      status: auth
    }

    console.log('App status',this.state);
    this.handleStatusChange = this.handleStatusChange.bind(this);
  }

  handleStatusChange(status) {

    console.log('App statusChange1',status);
    this.setState({
      status
    })
    console.log('App statusChange2',status);

  }

  componentWillMount() {
    console.log('WillMount');
  }
  componentDidMount() {
    console.log('DidMount');
  }
  componentWillReceiveProps(newProps) {
    console.log('WillReceiveProps',newProps);
  }
  shouldComponentUpdate(newProps, newState) {
    console.log('shouldUpdate',newProps,' ',newState);
    return true;
  }
  componentWillUpdate(nextProps, nextState) {
    console.log('WillUpdate',nextProps,' ',nextState);
  }
  componentDidUpdate(prevProps, prevState) {
    console.log('DidUpdate',prevProps,' ',prevState);
  }
  componentWillUnmount() {
    console.log('WillUnmount');
  }

  isUserLoggedIn() {
    console.log('isUserLoggedIn',this.state.status);
    if(this.state.status)
    {
      return true;
    }
    else {
      return false;
    }
  }
  render() {
    return (
        <div className="App">
          {console.log('App')}
            <nav className="navbar navbar-inverse">
              <div className="container-fluid">
                <ul className="nav navbar-nav">
                  <li><Link to={"/"}>Home</Link></li>
                </ul>
              </div>
            </nav>
            <Sign status={this.state.status} onStatusChange={this.handleStatusChange}/>
            {/* 
            <Context.Consumer>
              {({status, toggleStatus}) => {
                console.log('status',status);
                (
                <button
                  onClick={toggleStatus}
                  >
                  Toggle Theme
                </button>
              )}}
            </Context.Consumer>
            */
            }
            <Switch>
              <Route exact path="/" render={() => (
                this.isUserLoggedIn() ? (
                  <Home status={this.state.status} onStatusChange={this.handleStatusChange}/>
                ) : (
                  <Redirect to="/signin" />
                )
              )}/>

              <Route exact path="/signin" render={() => (
                this.isUserLoggedIn() ? (
                  <Redirect to="/" />
                ) : (
                  <Signin status={this.state.status} onStatusChange={this.handleStatusChange}/>
                )
              )}/>

              <Route exact path="/signup" render={() => (
                this.isUserLoggedIn() ? (
                  <Redirect to="/" />
                ) : (
                  <Signup status={this.state.status} onStatusChange={this.handleStatusChange}/>
                )
              )}/>

              <Route exact path="/signout" render={() => (
                this.isUserLoggedIn() ? (
                  <Home />
                ) : (
                  <Signout />
                )
              )}/>
              
            </Switch>
            <footer>
              <p>&copy; 2018. All Rights Reserved!</p>
            </footer>
        </div>
    );
  }
}

export default App;



    /*
    fetch('http://localhost:1827/get?q1=sarvesh&q2=test', {
      method: 'get'
    })
    .then(response => response.json())
    .then(json => console.log('get',json));
    */

    /*
    fetch('http://localhost:1827/testget/sarvesh', {
      method: 'get'
    })
    .then(response => response.json())
    .then(json => console.log('testget',json));
    */

    //fetch('http://localhost:1827/testpost',{
      //method: 'post',
      //headers: {
        //'Accept': 'application/json, text/plain, */*',
        //'Content-Type': 'application/json'
      //},
      //body: JSON.stringify({name:"testpost", age:30, city:"New York"})
    //})
    //.then(response => response.json())
    //.then(json => console.log('testpost',json));

    /*
    fetch('http://localhost:1827/post', {
      method: 'post',
      body: 'post'
    })
    .then(response=> response.text())
    .then(text => console.log('post',text))
    .catch(error => console.error('error', error));
    */
