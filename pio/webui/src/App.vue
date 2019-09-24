<template>
  <div id="app" class>
    <nav
      class="navbar is-primary"
      role="navigation"
      aria-label="main navigation"
    >
      <div class="navbar-brand">
        <a class="navbar-item is-size-5 has-text-weight-bold" href="/"
          >miniDenko</a
        >
        <a
          role="button"
          class="navbar-burger"
          aria-label="menu"
          aria-expanded="false"
        >
          <span aria-hidden="true"></span>
          <span aria-hidden="true"></span>
          <span aria-hidden="true"></span>
        </a>
      </div>
    </nav>

    <div class="container">
      <b-notification
        :active.sync="showConnectionWarn"
        type="is-warning"
        aria-close-label="Close notification"
        role="alert"
        >The device is not connected to WiFi AP(Client).</b-notification
      >
      <b-tabs expanded v-model="activeTab" type="is-box" v-if="inited">
        <b-tab-item label icon="list" icon-pack="fas">
          <messages-page></messages-page>
        </b-tab-item>
        <b-tab-item icon="cog" icon-pack="fas">
          <device-page></device-page>
        </b-tab-item>
      </b-tabs>
    </div>
    <b-loading :is-full-page="false" :active="!inited"></b-loading>
  </div>
</template>

<script>
import { mapActions, mapState, mapGetters } from 'vuex';

import DevicePage from '@/components/DevicePage';
import MessagesPage from '@/components/MessagesPage';

export default {
  name: 'app',
  components: {
    DevicePage,
    MessagesPage,
  },
  computed: {
    ...mapState(['inited', 'deviceInfo']),
    ...mapGetters(['isDeviceConnected', 'isDeviceApMode']),
    showConnectionWarn() {
      return !this.isDeviceApMode && !this.isDeviceConnected;
    },
  },
  data() {
    return {
      activeTab: 0,
    };
  },
  methods: {
    ...mapActions(['init']),
  },
  async mounted() {
    await this.init();
  },
};
</script>

<style lang="scss">
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #2c3e50;
}
</style>
