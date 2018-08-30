import React, { Component } from 'react';
//import logo from '../logo.svg';
import '../style/style.css';

class App extends Component {
  
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

  render() {
    return (
        <div className="App">
            <header className="App-header">
                {//<img src={logo} className="App-logo" alt="logo" />
                }
                <h1 className="App-title">Welcome to React</h1>
            </header>
            <p className="App-intro">
                To get started, edit <code>src/App.js</code> and save to reload.
            </p>
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