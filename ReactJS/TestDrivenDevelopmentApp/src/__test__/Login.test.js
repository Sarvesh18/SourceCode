import React from 'react';

import renderer from 'react-test-renderer';

import { shallow, mount, render } from 'enzyme';
import Login from '../js/Login';

/*
import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';

it('renders without crashing', () => {
  const div = document.createElement('div');
  ReactDOM.render(<App />, div);
  ReactDOM.unmountComponentAtNode(div);
});
*/

describe('Login Component', () => {
 
    it('should render without throwing an error', () => {
        expect(shallow(<Login />).find('form.login').exists()).toBe(true)
    })

    it('renders a email input', () => {
        expect(shallow(<Login />).find('#email').length).toEqual(1)
    })
    
    it('renders a password input', () => {
        expect(shallow(<Login />).find('#password').length).toEqual(1)
    })
})

/*
test('Test Component', () => {
    const todo = { id: 1, done: false, name: 'Buy Milk' };
    const wrapper = mount(
      <Todo todo={todo} />
    );
    const p = wrapper.find('.toggle-todo');
    expect(p.text()).toBe('Buy Milk');
});
*/

describe('Email input', () => {
  
    it('should respond to change event and change the state of the Login Component', () => {
     
        const wrapper = shallow(<Login />);
        wrapper.find('#email').simulate('change', {target: {name: 'email', value: 'blah@gmail.com'}});
        expect(wrapper.state('email')).toEqual('blah@gmail.com');
    })
})
   
describe('Password input', () => {
    
    it('should respond to change event and change the state of the Login Component', () => {
     
        const wrapper = shallow(<Login />);
        wrapper.find('#password').simulate('change', {target: {name: 'password', value: 'cats'}});
     
        expect(wrapper.state('password')).toEqual('cats');
    })
})

describe('Snapshot', () => {
    it('renders correctly', () => {
        const tree = renderer.create(
          <Login />
        ).toJSON();
        expect(tree).toMatchSnapshot();
    });
})


/*test('Link changes the class when hovered', () => {
    const component = renderer.create(
      <Link page="http://www.facebook.com">Facebook</Link>,
    );
    let tree = component.toJSON();
    expect(tree).toMatchSnapshot();
  
    // manually trigger the callback
    tree.props.onMouseEnter();
    // re-rendering
    tree = component.toJSON();
    expect(tree).toMatchSnapshot();
  
    // manually trigger the callback
    tree.props.onMouseLeave();
    // re-rendering
    tree = component.toJSON();
    expect(tree).toMatchSnapshot();
})*/