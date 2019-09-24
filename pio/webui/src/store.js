import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';
import orderBy from 'lodash/orderBy';
import uniqBy from 'lodash/uniqBy';
import min from 'lodash/min';
import max from 'lodash/max';
import get from 'lodash/get';
import pickBy from 'lodash/pickBy';
import pick from 'lodash/pick';
import cloneDeep from 'lodash/cloneDeep';
import createPersistedState from 'vuex-persistedstate';

Vue.use(Vuex);

const defaultMessages = [
  {
    value: 'Hi, This is a message saved on the browser.',
    monospace: false,
    scroll: true,
  },
  {
    value: 'From miniDenko with <3',
    monospace: false,
    scroll: true,
  },
  {
    value: '0x42',
    monospace: false,
    scroll: false,
  },
];

export default new Vuex.Store({
  state: {
    inited: false,
    isLoading: {
      deviceSettings: true,
    },
    deviceInfo: null,
    deviceSettings: {},
    scanResults: [],
    messages: cloneDeep(defaultMessages),
  },
  getters: {
    isDeviceConnected(state) {
      return get(state.deviceInfo, 'wifi_c', true);
    },
    isDeviceApMode(state) {
      return get(state.deviceSettings, 'wifiMode', 0) == 2;
    },
    savedMessages(state) {
      return (state.deviceSettings.messages || []).filter(v => v.value);
    },
  },
  mutations: {
    setInited(state, data) {
      state.inited = data;
    },
    setDeviceInfo(state, data) {
      state.deviceInfo = data;
    },
    setDeviceSettings(state, data) {
      state.deviceSettings = data;
    },
    addScanResults(state, data) {
      state.scanResults = orderBy(
        uniqBy([...state.scanResults, ...data], 'ssid'),
        'rssi',
        'desc'
      );
    },
    setIsLoading(state, data) {
      state.isLoading = Object.assign({}, state.isLoading, data);
    },
    setIsLoadingAll(state, data) {
      for (const [key] of Object.entries(state.isLoading)) {
        state.isLoading[key] = data;
      }
    },
    addMessage(state, data) {
      if (!data.value) {
        return;
      }
      state.messages = state.messages.concat(data);
    },
    editMessage(state, { oldMsg, newMsg }) {
      // const identify = v => JSON.stringify(v);
      // const oldMsgIdent = identify(oldMsg);
      // const ind = state.messages.findIndex(v => oldMsgIdent === identify(v));
      const ind = state.messages.indexOf(oldMsg);
      Vue.set(state.messages, ind, newMsg);
    },
    deleteMessage(state, data) {
      const ind = state.messages.indexOf(data);
      ind !== -1 && state.messages.splice(ind, 1);
    },
    setMessages(state, data) {
      state.messages = data;
    },
  },
  actions: {
    async init({ dispatch, commit, state }) {
      await dispatch('fetchDeviceInfo');
      await dispatch('fetchDeviceSettings');
      commit('setIsLoadingAll', false);

      // merge DSM + LSM (w/o slot props)
      const identify = v => JSON.stringify(v);
      const messages = uniqBy(
        state.messages
          .map(msg => pickBy(msg, (_, k) => k !== 'slot'))
          .concat(state.deviceSettings.messages)
          .filter(v => v.value),
        identify
      );

      // add slot plops from DSM
      const dsmIds = state.deviceSettings.messages.map(v => identify(v));
      commit(
        'setMessages',
        messages.map(lsm => {
          const lId = identify(lsm);
          const slot = dsmIds.findIndex(dId => dId === lId);
          return { ...lsm, slot };
        })
      );

      commit('setInited', true);
    },
    async fetchDeviceInfo({ commit }) {
      const { data } = await axios.get('/api/device');
      commit('setDeviceInfo', data);
    },
    async fetchDeviceSettings({ commit }) {
      const { data } = await axios.get('/api/settings');
      commit('setDeviceSettings', data);
    },
    async postDeviceSettings({ commit }, body) {
      const { data } = await axios.post('/api/settings', body);
      commit('setDeviceSettings', data);
    },
    async postMessage(_, msg) {
      await axios.post(
        '/api/message',
        pick(msg, ['value', 'monospace', 'scroll'])
      );
    },
    async fetchScanResults({ commit }) {
      const { data } = await axios.get('/api/wifi/scan');
      commit(
        'addScanResults',
        data.map(ap => {
          ap.rssi = ap.rssi || -90 + 0.1;
          ap.signal = Math.ceil(
            ((min([max([-90 + 0.1, ap.rssi]), -30 - 0.1]) + 90) / 60) * 5
          );
          return ap;
        })
      );
    },
  },
  plugins: [
    createPersistedState({
      paths: ['messages'],
    }),
  ],
});
