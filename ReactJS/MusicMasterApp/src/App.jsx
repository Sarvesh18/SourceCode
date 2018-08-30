import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import MusicMaster from './MusicMaster';

class App1 extends Component {
  constructor(props) {
    super(props);
    this.state = {
      test: 'TestApp1'
    }
  }
  compountWillMount() {
    console.log("WillMount");
  }
  componentDidMount() {
    console.log("DidMount");
    console.log(this.props.prop1);
    console.log(this.state.test);
  }


  render() {
    return (
       <div className="App">
         <p>{this.state.test}</p>
         <header className="App-header">
           <img src={logo} className="App-logo" alt="logo" />
           <h1 className="App-title">Welcome</h1>
           </header>
           <p className="App-intro">
             To get started, edit <code>src/App.js</code> and save to reload.
           </p>
           <MusicMaster />
        </div>
    );
  }
}

export default App1;
