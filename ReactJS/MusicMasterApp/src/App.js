import React, { Component } from 'react';
import './App.css';
import App1 from './App.jsx';

class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      test: 'TestApp'
    }
  }

  func(p) {
    this.setState({
      test: 'p'
    });
  }

  render() {
    return (
      <div className="App">
        <p>{this.state.test}</p>
        <App1
          prop1={this.state.test}
        />
      </div>
    );
  }
}

export default App;
