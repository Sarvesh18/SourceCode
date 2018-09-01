import React, { Component } from 'react';

class Sign extends Component {
  constructor(props) {
    super(props);
    console.log('Sign props',props);
  }
  handleChange(e) {
    console.log('e',e);
    this.props.onStatusChange(e);
  }
  render() {
      return (
            <div>
                <button type="button" onClick={() => this.handleChange(true)}>SignIn</button>
                <button type="button" onClick={() => this.handleChange(false)}>SignOut</button>
            </div>
      )
  }
}
export default Sign;