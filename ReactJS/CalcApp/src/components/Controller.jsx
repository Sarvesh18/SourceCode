import React, { Component } from 'react';
import './style.css';

import {connect} from 'react-redux';
import {bindActionCreators} from 'redux';
import {add,sub,mul,div,concat,equal} from '../actions';

class Controller extends Component {
  componentDidMount() {
    console.log('componentDidMount Controller');
  }
  equal(vvv) {
    console.log('equal',vvv);
  }
  render() {
    return (
      <div className="grid-container">
        {console.log('return Controller')}
        <div className="item0 grid-item"
          onClick={()=> this.equal(this.props.value[3])}> = </div>
      </div>
    );
  }
}

function mapStateToProps(state) {
    console.log('mapStateToProps Controller',state);
    return {value:state}
}

function mapDispatchToProps(dispatch) {
  //console.log('mapDispatchToProps Display',dispatch);
  return bindActionCreators({add,sub,mul,div,concat,equal},dispatch);
}

export default connect(mapStateToProps,mapDispatchToProps)(Controller);
